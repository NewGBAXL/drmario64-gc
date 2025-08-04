#ifndef GC_H
#define GC_H

#include "libultra.h"

void DoMalloc(s32 arg0);
void DoFree(s32 arg0);

void fn_2_5B98C(void);
void _gc_song_stop(s32 arg0);
void gc_song_stop(u32 arg0);

s32 fn_2_5EEA0(s32 arg0);

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

extern s32 lbl_2_data_25120;
extern s32 lbl_2_bss_21437C;

extern s32 lbl_2_bss;
extern s32 lbl_2_bss_2243FC;
extern s32 lbl_2_bss_224400;
extern s32 lbl_2_bss_210A68;

extern s32 DAT_809c57d4;
extern u32 lbl_2_bss_212D8C;
extern s32 DAT_809c57a8;
extern s32 lbl_2_bss_224430;
extern s32 DAT_809c57d0;
extern s32 lbl_2_bss_212D88;
extern s32 lbl_2_bss_224638;
extern s32 lbl_2_bss_224654;

extern s32 lbl_2_data_25358[3];

extern s32 DAT_8099bac8;
extern s32 DAT_809b1e00;
extern s32 DAT_809b1e08;
extern s32 DAT_809b1e04;
extern s32 DAT_807a1060;
extern s32 DAT_809b3e10;
extern s32 DAT_8099bac0;
extern s32 lbl_2_bss_1FA728;
//extern s32 lbl_2_data_25120;
extern s32 DAT_809b1ae8;
extern s32 DAT_8099bac4;
extern s32 lbl_2_data_25274 = 0xFFFFFFFD;




#endif
