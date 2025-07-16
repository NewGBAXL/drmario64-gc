#ifndef GC_H
#define GC_H

#include "libultra.h"

void DoMalloc(s32 arg0);
void DoFree(s32 arg0);

void gc_soundQuit(void);
s32 gc_songPlay(u32 arg0, s32 arg1);

// data

extern __OSCurrHeap;
extern alloc_counter;
extern fn_2_5BBC8();
extern fn_2_3B4(s32 arg0, s32 arg1);

u32 cho;
u32 revH;
s32 songTbl;
extern s32 lastsong_id;

extern s32 lbl_2_bss_212DB4;
extern s32* lbl_2_bss_213054;
extern fn_80019D00();

extern s16* EFB_bufferp;
//extern __OSCurrHeap;


#endif
