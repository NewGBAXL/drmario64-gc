#include <types.h>
#include "unzip.h"

// NOTE: the existing declarations of DoMalloc in this repo (include/gc.h,
// include/game/memory.h) say `void DoMalloc(int size)`, but the actual
// disassembly of DoMalloc (0x800123FC) shows it returns the pointer from
// OSAllocFromHeap in r3 -- the existing declarations appear to be wrong.
// Declaring it correctly here rather than silently editing those files.
extern void* DoMalloc(s32 size);

// expand_gzip
// Read the big-endian u32 outputLength field at blob offset +4.
u32 expand_gzip(void* src) {
    u8* p = (u8*) src + 4;
    return ((u32) p[0] << 24) | ((u32) p[1] << 16) | ((u32) p[2] << 8) |
           (u32) p[3];
}

// fn_8001A780
// LZSS-style decompressor. See unzip.h for the format description.
void* fn_8001A780(void* srcParam, void* dst) {
    /*u8* src = (u8*)srcParam;
    u8* base;
    u32 outputLength, literalStreamOffset, matchStreamOffset;
    u8* literalStream;
    u8* matchStream;
    u8* outEnd;
    u8* out;
    u32 bitsRemaining;
    u32 controlWord;
    u8* bitstream;

    if (dst == NULL) {
        // outputLength, read here purely to size the allocation; the
        // header is re-read again below via the normal field parse.
        u32 size = ((u32) src[4] << 24) | ((u32) src[5] << 16) |
                   ((u32) src[6] << 8) | (u32) src[7];
        dst = DoMalloc(size);
    }

    if (dst == NULL) {
        return NULL;
    }

    base = src + 4;
    outputLength = ((u32) base[0] << 24) | ((u32) base[1] << 16) |
                   ((u32) base[2] << 8) | (u32) base[3];
    matchStreamOffset = ((u32) base[4] << 24) | ((u32) base[5] << 16) |
                        ((u32) base[6] << 8) | (u32) base[7];
    literalStreamOffset = ((u32) base[8] << 24) | ((u32) base[9] << 16) |
                          ((u32) base[10] << 8) | (u32) base[11];

    literalStream = src + literalStreamOffset;
    matchStream = src + matchStreamOffset;
    out = (u8*) dst;
    outEnd = out + outputLength;
    bitstream = src + 16;
    bitsRemaining = 0;
    controlWord = 0; // overwritten by the first refill before use

    while (out < outEnd) {
        if (bitsRemaining == 0) {
            controlWord = ((u32) bitstream[0] << 24) |
                          ((u32) bitstream[1] << 16) |
                          ((u32) bitstream[2] << 8) | (u32) bitstream[3];
            bitsRemaining = 32;
            bitstream += 4;
        }

        if (controlWord & 0x80000000) {
            // literal
            *out++ = *literalStream++;
        } else {
            // match: 16-bit big-endian value, 12-bit distance + 4-bit
            // length nibble
            u32 raw = ((u32) matchStream[0] << 8) | (u32) matchStream[1];
            matchStream += 2;

            u32 distance = raw & 0xFFF;
            u32 lengthNibble = raw >> 12;
            u8* matchSrc = out - distance - 1;
            u32 matchLen;

            if (lengthNibble == 0) {
                matchLen = (u32) *literalStream++ + 18;
            } else {
                matchLen = lengthNibble + 2;
            }

            while (matchLen > 0) {
                *out++ = *matchSrc++;
                matchLen--;
            }
        }

        controlWord <<= 1;
        bitsRemaining--;
    }

    return out;*/
}
