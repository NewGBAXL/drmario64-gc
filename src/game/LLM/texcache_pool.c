#include "texcache_pool.h"
#include <dolphin/os/OSAlloc.h>
#include <dolphin/os/OSCache.h>

// NOTE ON VERIFICATION:
// This file was NOT compiled against mwcc or diffed via objdiff -- the
// original GC ISO (orig/GPZJ01) was not available in the environment this
// was written in. Field/struct layout and control flow were derived by
// careful manual reading of the disassembly, and the four unlink cases
// (node==head, node==tail, node==both, node==middle) were each
// individually cross-checked against the raw asm before writing this.
// Still: this is a strong starting point for objdiff iteration, NOT a
// confirmed match. Run `ninja` + objdiff locally to verify and adjust.
//
// NOTE ON NAMING:
// All function and global names here are MY proposed names, not confirmed
// symbols. Each one notes its original fn_/lbl_ placeholder address so it
// stays cross-referenceable against the disassembly until/unless these
// get applied to symbols.txt.
//
// Confirmed field semantics (cross-checked against the insert-at-head and
// unlink blocks in TexCachePool_FindAndTouch / was fn_80010A74):
//   sTexCachePoolHead (-26056) = most-recently-used end / insert point
//   sTexCachePoolTail (-26060) = least-recently-used end / eviction point
//   node->prev (+0x00) = link toward head (newer)
//   node->next (+0x04) = link toward tail (older)
//   search/invalidate traversal starts at head and walks via node->next
//
// Globals below are placed in declaration order to land in the same .bss
// region the disassembly references (0x801bcaf0 onward), per this
// project's convention (see src/game/sys.c). Sizes must stay exact or the
// following symbols will shift.

// was lbl_801bcaf0, 0x801bcaf0
extern static s32 sTexCachePoolActiveCount; // active/in-use node count; compared
// against TEXCACHE_POOL_SIZE in
// TexCachePool_Acquire
// was lbl_801bcaf4, 0x801bcaf4
extern static TexCacheNode* sTexCachePoolTail; // LRU end
// was lbl_801bcaf8, 0x801bcaf8
extern static TexCacheNode* sTexCachePoolHead; // MRU end
// was lbl_801bcafc, 0x801bcafc
extern static TexCacheNode sTexCachePool[TEXCACHE_POOL_SIZE]; // node pool

// was lbl_800f4024, 0x800f4024, in a separate larger .bss region shared
// with renderer scratch data (vertex cache / matrix stack live further
// along the same blob; not yet split out). Only this leading slice is
// owned by this file.
static void* sTexCacheDataPtrs[TEXCACHE_POOL_SIZE]; // per-node backing
// data ptrs

// TexCachePool_Relink (was fn_80010818)
// Re-link the pool from the existing backing-pointer table, without
// (re)allocating. Used by n642Dolphin_AllchangeTexture.
void TexCachePool_Relink(void) {
    s32 i;
    for (i = 0; i < TEXCACHE_POOL_SIZE; i++) {
        TexCacheNode* node = &sTexCachePool[i];
        node->rangeStart = 0;
        node->data = sTexCacheDataPtrs[i];
        node->key2 = 0;
        node->key3 = 0;
        node->next = NULL;
        node->prev = NULL;
    }
}

// TexCachePool_Init (was fn_80010910)
// Allocate fresh 5120-byte backing storage for every node (freeing any
// existing allocation first), then re-link the pool exactly like
// TexCachePool_Relink. Called from GCNIS_nuGfxInit_relocate (and two
// other still-unidentified callers, fn_8000C0B8 / fn_8000C298, both
// 0x1E0 bytes and likely sibling nuGfxInit-family functions).
void TexCachePool_Init(void) {
    s32 i;
    for (i = 0; i < TEXCACHE_POOL_SIZE; i++) {
        if (sTexCacheDataPtrs[i] != NULL) {
            OSFreeToHeap(__OSCurrHeap, sTexCacheDataPtrs[i]);
        }
        sTexCacheDataPtrs[i] = OSAllocFromHeap(__OSCurrHeap,
            TEXCACHE_ENTRY_DATA_SIZE);
    }

    TexCachePool_Relink();
}

// TexCachePool_FindAndTouch (was fn_80010A74)
// Search the active list starting at head, walking toward tail, for a
// node matching (rangeStart, key2, key3). If found, unlink it and
// re-insert it at head (MRU promotion), returning its data pointer.
// Returns NULL on no match.
void* TexCachePool_FindAndTouch(u32 rangeStart, u16 key2, u16 key3) {
    TexCacheNode* node = sTexCachePoolHead;

    while (node != NULL) {
        if (node->rangeStart == rangeStart && node->key2 == key2 &&
            node->key3 == key3) {
            // unlink from doubly-linked active list
            if (node == sTexCachePoolHead && node == sTexCachePoolTail) {
                sTexCachePoolHead = NULL;
                sTexCachePoolTail = NULL;
            }
            else if (node == sTexCachePoolHead) {
                sTexCachePoolHead = node->next;
                sTexCachePoolHead->prev = NULL;
            }
            else if (node == sTexCachePoolTail) {
                sTexCachePoolTail = node->prev;
                sTexCachePoolTail->next = NULL;
            }
            else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
            node->next = NULL;
            node->prev = NULL;

            // re-insert at head (MRU promotion)
            if (sTexCachePoolTail == NULL) {
                sTexCachePoolHead = node;
                sTexCachePoolTail = node;
            }
            else {
                node->next = sTexCachePoolHead;
                sTexCachePoolHead->prev = node;
                sTexCachePoolHead = node;
            }

            return node->data;
        }
        node = node->next; // walk head -> tail
    }

    return NULL;
}

// TexCachePool_Acquire (was fn_80010B88)
// Obtain a node for use -- if the active count hasn't reached
// TEXCACHE_POOL_SIZE yet, scan the pool for a free slot (rangeStart == 0)
// and use it; otherwise steal the tail (least-recently-used) from the
// active list. Links the chosen node onto the active list at head,
// populates its key fields, returns its data ptr.
void* TexCachePool_Acquire(u32 rangeStart, u16 key2, u16 key3) {
    TexCacheNode* node;

    if (sTexCachePoolActiveCount < TEXCACHE_POOL_SIZE) {
        // scan the pool for the next never-used slot (rangeStart == 0)
        s32 i;
        for (i = 0; i < TEXCACHE_POOL_SIZE; i++) {
            if (sTexCachePool[i].rangeStart == 0) {
                break;
            }
        }
        node = &sTexCachePool[i];
        node->next = NULL;
        node->prev = NULL;
        sTexCachePoolActiveCount++;
    }
    else {
        // steal the tail (least-recently-used) from the active list
        node = sTexCachePoolTail;
        if (node == NULL) {
            // unreachable in practice: count >= POOL_SIZE implies tail is
            // non-null. Mirrors the asm's beq guard at 80010c34.
        }
        else if (node == sTexCachePoolHead && node == sTexCachePoolTail) {
            sTexCachePoolHead = NULL;
            sTexCachePoolTail = NULL;
        }
        else {
            // node == tail specifically here (it's always the tail by
            // definition of this branch), but the asm runs through the
            // same general unlink shape -- see the dead self-compare at
            // 80010c38 (cmplw r7,r7), which is consistent with this
            // eviction path being a specialization of the same unlink
            // logic used elsewhere, where the "node==head" leg became
            // unreachable/constant-folded for this specific call site.
            sTexCachePoolTail = node->prev;
            sTexCachePoolTail->next = NULL;
        }
        node->next = NULL;
        node->prev = NULL;
    }

    // insert at head
    if (sTexCachePoolTail == NULL) {
        sTexCachePoolHead = node;
        sTexCachePoolTail = node;
    }
    else {
        node->next = sTexCachePoolHead;
        sTexCachePoolHead->prev = node;
        sTexCachePoolHead = node;
    }

    node->rangeStart = rangeStart;
    node->key2 = key2;
    node->key3 = key3;

    return node->data;
}

// TexCachePool_GetOrCreate (was fn_80010D00)
// Top-level cache lookup-or-insert. arg0 is forwarded as the first arg to
// fn_8000A618 (the as-yet-unreversed GX upload routine); arg1/arg2/arg3
// are the (rangeStart, key2, key3) cache key; arg4-arg8 are additional
// upload parameters whose meaning isn't resolved yet.
void TexCachePool_GetOrCreate(void* arg0, u32 arg1, u32 arg2, u32 arg3,
    u32 arg4, u32 arg5, u32 arg6, u32 arg7,
    u32 arg8) {
    void* data = TexCachePool_FindAndTouch(arg1, (u16)arg2, (u16)arg3);

    if (data != NULL) {
        // cache hit: bump a hit counter. NOTE: the +12(r31) field accessed
        // here is a *different* global from the node pool base (r31, not
        // r6/r9) -- not yet identified; placeholder access omitted until
        // that base is resolved.
    }
    else {
        data = TexCachePool_Acquire(arg1, (u16)arg2, (u16)arg3);

        // fn_8000A618's full signature isn't resolved (it reads stack args
        // beyond what's set up here in other call paths); this call
        // mirrors only what this call site actually passes.
        fn_8000A618(data, arg0, arg2, arg3, arg4, arg5, arg6, arg7, arg8);

        DCFlushRange(data, TEXCACHE_ENTRY_DATA_SIZE);
        // miss counter bump, same caveat as the hit counter above
    }
}

// TexCachePool_InvalidateRange (was fn_80010DCC)
// Invalidate any active node whose rangeStart falls within
// [start, start+length). Walks head -> tail. Called directly by
// n642Dolphin_changeTexture.
void TexCachePool_InvalidateRange(u32 start, u32 length) {
    u32 end = start + length;
    TexCacheNode* node = sTexCachePoolHead;

    while (node != NULL) {
        TexCacheNode* next = node->next; // save before potential unlink

        if (node->rangeStart >= start && node->rangeStart < end) {
            node->rangeStart = 0;

            // unlink from active list
            if (node == sTexCachePoolHead && node == sTexCachePoolTail) {
                sTexCachePoolHead = NULL;
                sTexCachePoolTail = NULL;
            }
            else if (node == sTexCachePoolHead) {
                sTexCachePoolHead = node->next;
                sTexCachePoolHead->prev = NULL;
            }
            else if (node == sTexCachePoolTail) {
                sTexCachePoolTail = node->prev;
                sTexCachePoolTail->next = NULL;
            }
            else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
            node->next = NULL;
            node->prev = NULL;

            sTexCachePoolActiveCount--;

            // NOTE: asm has an additional check after the decrement
            // (80010e8c-80010e94) that infinite-loops (80010e98: b
            // 80010e98) if the count goes negative -- an assert/halt-style
            // guard. Omitted here as it has no clean C-level equivalent in
            // this codebase's idiom; flagging in case it matters for
            // matching.
        }

        node = next;
    }
}

// TexCachePool_Destroy (was fn_80010EA8)
// Free every node's backing allocation and clear the pointer table.
// Teardown counterpart to TexCachePool_Init.
void TexCachePool_Destroy(void) {
    s32 i;
    for (i = 0; i < TEXCACHE_POOL_SIZE; i++) {
        OSFreeToHeap(__OSCurrHeap, sTexCacheDataPtrs[i]);
        sTexCacheDataPtrs[i] = NULL;
    }
}