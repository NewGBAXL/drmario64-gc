#ifndef DR_MARIO_GC_H
#define DR_MARIO_GC_H

#include "libultra.h"
#include "PR/ultratypes.h"

s32 main(void);
void drMarioRetrace(bool arg0);

extern s32 eeprom_bufferp;
extern s32 Gzip_bufferp;
extern s32 Heap_bufferp;

extern s32* mainproc;

extern s32 lbl_2_bss_0;
extern s32 DAT_807a13a8;
extern void (*subproc_nuGfxFunc)(void);



#endif
