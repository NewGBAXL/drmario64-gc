#ifndef UNZIP_H
#define UNZIP_H

#include <types.h>

// game/unzip.c
//
// A custom LZSS-style compression format (NOT real gzip/DEFLATE, despite
// the "gzip" naming used by callers like ExpandGZip in util.c).
//
// UNRESOLVED: every size/offset field below is read starting at blob
// offset +4, not +0 -- meaning there are 4 unidentified bytes at the very
// start of the blob (perhaps a magic number/tag). Not guessing at what
// they are; treat offset +0..+3 as unknown until confirmed.
//
// Layout from offset +4 (16 bytes total before the bitstream):
//
//   +4  u32 outputLength          (big-endian; total decompressed byte
//                                   count. This single field is read
//                                   independently by three different call
//                                   sites: expand_gzip(), the malloc-size
//                                   check in fn_8001A780()'s prologue
//                                   when dst==NULL, and the main decode
//                                   loop's termination sentinel. All three
//                                   reads are the same 4 bytes.)
//   +8  u32 literalStreamOffset   (offset from blob start to the literal
//                                   byte stream, big-endian, named fieldC
//                                   in-source until a real name is found)
//   +12 u32 matchStreamOffset     (offset from blob start to the match
//                                   (distance/length) stream, big-endian,
//                                   named fieldB in-source)
//   +16 ... compressed control-bit stream follows here ...
//
// The control-bit stream is consumed 32 bits at a time, MSB first. For
// each bit:
//   1 -> literal: copy one byte from the literal stream to output.
//   0 -> match: read a 16-bit big-endian value from the match stream,
//        split into a 12-bit distance (bits 0-11) and 4-bit length
//        nibble (bits 12-15). If the length nibble is 0, an extra
//        length byte is read from the literal stream and 18 is added
//        (long match, encodes lengths 18-273); otherwise the match
//        length is nibble+2 (short match, encodes lengths 2-17). The
//        match then copies length bytes from output[-(distance+1)] to
//        the current output position (the +1 is because distance 0
//        means "1 byte back", not "0 bytes back").
// Decoding stops once outputLength bytes have been written.

// expand_gzip
// Reads just the big-endian u32 outputLength header field (blob offset
// +4) from a compressed blob.
u32 expand_gzip(void* src);

// fn_8001A780
// The real decompressor. If dst is NULL, allocates a buffer via DoMalloc
// sized from the blob's outputLength header field. Decodes the LZSS-style
// stream described above into dst. Returns the final output cursor
// (dst + bytes written), or NULL if dst was NULL and allocation failed.
void* fn_8001A780(void* src, void* dst);

#endif
