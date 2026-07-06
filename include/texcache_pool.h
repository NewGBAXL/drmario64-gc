#ifndef TEXCACHE_POOL_H
#define TEXCACHE_POOL_H

#include <types.h>

// Reverse-engineered from the unsplit .text gap between nu/nusys.c and
// libultra/gu/coss.c (0x80010818 - 0x80010F24).
//
// This is a fixed-size pool (618 entries) of intrusively-linked nodes used
// as a texture/data cache keyed on (addr range, u16, u16). Each node owns a
// 5120-byte heap allocation (likely a single GX texture tile's worth of
// converted N64->GX texture data, given the call site in n642Dolphin.c).
//
// The names below (functions, globals, struct fields) are MY proposed
// names based on behavior, not confirmed symbols. The actual symbols.txt
// entries are still fn_80010818 etc. -- each declaration below notes its
// original placeholder address in a comment so it can be cross-referenced
// against the disassembly or matched up if you want to apply these names
// in symbols.txt. Treat as a renaming proposal, not as established fact.

#define TEXCACHE_POOL_SIZE 618
#define TEXCACHE_ENTRY_DATA_SIZE 5120

typedef struct TexCacheNode {
    /* 0x00 */ struct TexCacheNode* prev; // toward head (MRU)
    /* 0x04 */ struct TexCacheNode* next; // toward tail (LRU)
    /* 0x08 */ u32 rangeStart;
    /* 0x0C */ void* data;
    /* 0x10 */ u16 key2;
    /* 0x12 */ u16 key3;
} TexCacheNode; // size 0x14

// TexCachePool_Relink (was fn_80010818)
// Re-link the node pool using whatever data pointers are already present
// in the backing pointer table (no allocation). Called by
// n642Dolphin_AllchangeTexture.
void TexCachePool_Relink(void);

// TexCachePool_Init (was fn_80010910)
// Allocate 5120-byte backing storage for all 618 nodes via
// OSAllocFromHeap(__OSCurrHeap, ...) and link the pool. Frees any existing
// allocation first. Called from GCNIS_nuGfxInit_relocate.
void TexCachePool_Init(void);

// TexCachePool_FindAndTouch (was fn_80010A74)
// Search the active list for a node matching (rangeStart == arg0,
// key2 == arg1, key3 == arg2). If found, unlink it and re-insert it at
// the head (MRU promotion), returning its data pointer; otherwise return
// NULL.
void* TexCachePool_FindAndTouch(u32 rangeStart, u16 key2, u16 key3);

// TexCachePool_Acquire (was fn_80010B88)
// Obtain a node for use: pull the next free slot from the pool while
// under capacity, otherwise evict the least-recently-used active node.
// Links the chosen node onto the active list (MRU end), populates its key
// fields, and returns its data pointer.
void* TexCachePool_Acquire(u32 rangeStart, u16 key2, u16 key3);

// TexCachePool_GetOrCreate (was fn_80010D00)
// Top-level cache lookup-or-insert entry point. On cache hit (via
// TexCachePool_FindAndTouch), bumps a hit counter. On miss, acquires a
// node, uploads/converts texture data via fn_8000A618, and flushes the
// data cache range.
void TexCachePool_GetOrCreate(void* arg0, u32 arg1, u32 arg2, u32 arg3,
    u32 arg4, u32 arg5, u32 arg6, u32 arg7,
    u32 arg8);

// TexCachePool_InvalidateRange (was fn_80010DCC)
// Invalidate any active-list node whose rangeStart falls within
// [start, start+length). Called directly by n642Dolphin_changeTexture.
void TexCachePool_InvalidateRange(u32 start, u32 length);

// TexCachePool_Destroy (was fn_80010EA8)
// Free all 618 nodes' backing allocations via
// OSFreeToHeap(__OSCurrHeap, ...) and zero the pointer table. Teardown
// counterpart to TexCachePool_Init.
void TexCachePool_Destroy(void);

#endif