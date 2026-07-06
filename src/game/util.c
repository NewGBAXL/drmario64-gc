#include <types.h>
#include "util.h"
#include "unzip.h"

// ExpandGZip
// Thin wrapper: read the embedded decompressed-size header via
// expand_gzip(), run the real decompressor (fn_8001A780, in unzip.c) for
// its side effect of writing to dst, then round (dst + size) up to 8-byte
// alignment and return it. fn_8001A780's return value is discarded.
void* ExpandGZip(void* src, void* dst) {
    u32 unused;
    u32 size = expand_gzip(src);
    fn_8001A780(src, dst);
    return (void*) (((u32) dst + size + 7) & ~7);
}

// WrapI
// Wrap val into [lo, hi). Computes a proper (non-truncating) modulo so
// negative offsets wrap correctly, then offsets back into [lo, hi).
int WrapI(int lo, int hi, int val) {
    int offset = val - lo;
    int range = hi - lo;
    int rem = offset - (offset / range) * range;
    if (rem < 0) {
        rem += range;
    }
    return rem + lo;
}

// NOTE: unconfirmed rodata constant at 0x80080538 (size 0x8, oddly large
// for an f32 -- possibly misjudged symbol bounds). Used as the epsilon
// threshold below; using 0.0f as a placeholder until the real value is
// extracted from rodata.
#define WRAPF_EPSILON 0.0f

static inline f32 fabs32(f32 x) {
    return x < 0.0f ? -x : x;
}

// WrapF
// Float equivalent of WrapI.
f32 WrapF(f32 lo, f32 hi, f32 val) {
    f32 range, offset;
 
    if (val >= lo && val < hi) {
        return val;
    }
 
    range = hi - lo;
    offset = val - lo;
 
    // Division only runs when |range| <= |offset| (i.e. the value could
    // actually be more than one range-width away); otherwise a single
    // wrap (the += range below) suffices and the division is skipped.
    if (fabs32(range) <= fabs32(offset)) {
        offset = offset - ((f32) (s32) (offset / range)) * range;
    }
 
    if (offset < 0.0f) {
        offset += range;
    }
 
    return offset + lo;
}
