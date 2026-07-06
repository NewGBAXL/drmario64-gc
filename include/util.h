#ifndef UTIL_H
#define UTIL_H

#include <types.h>

// game/util.c

// ExpandGZip
// Decompress a custom LZ-compressed asset blob (see unzip.c) into dst,
// returning the end-of-output pointer rounded up to 8-byte alignment.
void* ExpandGZip(void* src, void* dst);

// WrapI
// Wrap val into the range [lo, hi), handling negative offsets correctly
// (i.e. proper modulo, not C's truncating remainder).
int WrapI(int lo, int hi, int val);

// WrapF
// Float equivalent of WrapI: wrap val into the range [lo, hi).
f32 WrapF(f32 lo, f32 hi, f32 val);

#endif
