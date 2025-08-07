#include <types.h>
#include <dolphin/os/OSAlloc.h>
#include "libultra.h"

int lbl_801bcad8 = 0;
OSHeapHandle lbl_800f30c0;
OSHeapHandle lbl_800f30c4;
Mtx lbl_801bca94;
Mtx lbl_800f31f4;
Mtx lbl_800f3274;

extern lbl_8006a8f0;
extern lbl_8006a8f4;
extern lbl_8006a8f8;
extern lbl_8006a8c0;
extern lbl_8006a8fc;
extern lbl_800f3234;
extern lbl_800f30dc;
extern lbl_800bde00;

void GCNIS_nuGfxInit_relocate(void) {
    fn_8000bf24();
    OSSetCurrentHeap(lbl_800f30c0);
    if (OSCheckHeap(lbl_800f30c0) == -1) {
        NPC_ErrorPrint(0, "nusys.c", 0x18ab, "Heap Error", 0, 0, 0);
    }
    if (lbl_800f30c4 != lbl_800f30c0) {
        NPC_ErrorPrint(0, "nusys.c", 0x18ac, "Break! hCurrentHeap", 0, 0, 0);
    }
    PSMTXIdentity(&lbl_801bca94);
    PSMTXIdentity(&lbl_800f31f4);
    PSMTXIdentity(&lbl_800f3274);
    C_MTXOrtho((double)lbl_8006a8f0, (double)lbl_8006a8f4, (double)lbl_8006a8f0, (double)lbl_8006a8f8,
        (double)lbl_8006a8c0, (double)lbl_8006a8fc, &lbl_800f3234);
    fn_8000bd10();
    lbl_800f30dc = lbl_800bde00;
    fn_80010910();
    fn_800077a0();
}

int nuContInit(void) {
    fn_80017528();
    return 0;
}

void fn_8000c5a8(void) {
    lbl_801bcad8 = 0;
}

void fn_8000c5b8(void(*arg0)(s32)) {
    lbl_801bcad8 = 1;
    while (lbl_801bcad8 != 0) {
        arg0(0);
    }
}

//void fn_8000c61c(int *arg0,int *arg1)

//void fn_8000c6a0(int arg0)

//int fn_8000ca60(void)

//void fn_8000cbec(uint *arg0)

//PADtoN64, tentative, it converts the GameCube controller
//pad input to N64 controller input format
//todo: use defs to make the buttons readable
u32 fn_80010228(u16 arg0) {
    u32 uVar1;

    uVar1 = 0;
    if ((arg0 & 1) != 0) {
        uVar1 = uVar1 | 0x200;
    }
    if ((arg0 & 2) != 0) {
        uVar1 = uVar1 | 0x100;
    }
    if ((arg0 & 4) != 0) {
        uVar1 = uVar1 | 0x400;
    }
    if ((arg0 & 8) != 0) {
        uVar1 = uVar1 | 0x800;
    }
    if ((arg0 & 0x10) != 0) {
        uVar1 = uVar1 | 0x2000;
    }
    if ((arg0 & 0x20) != 0) {
        uVar1 = uVar1 | 0x10;
    }
    if ((arg0 & 0x40) != 0) {
        uVar1 = uVar1 | 0x20;
    }
    if ((arg0 & 0x100) != 0) {
        uVar1 = uVar1 | 0x8000;
    }
    if ((arg0 & 0x200) != 0) {
        uVar1 = uVar1 | 0x4000;
    }
    if ((arg0 & 0x400) != 0) {
        uVar1 = uVar1 | 0x1;
    }
    if ((arg0 & 0x800) != 0) {
        uVar1 = uVar1 | 0x8;
    }
    if ((arg0 & 0x1000) != 0) {
		uVar1 = uVar1 | 0x1000;
    }
    return uVar1;
}

void nuContQueryRead(u16* arg0) {
    int* piVar1;
    int iVar2;

    iVar2 = 0;
    do {
        piVar1 = (int*)fn_800179C4(iVar2); //GetPad
        if (*piVar1 == 1) {
            *arg0 = 5;
            *(u8*)(arg0 + 1) = 0;
            *(u8*)((int)arg0 + 3) = 0;
        }
        else {
            *arg0 = 0;
            *(u8*)(arg0 + 1) = 0;
            *(u8*)((int)arg0 + 3) = 0;
        }
        ++iVar2;
        arg0 += 2;
    } while (iVar2 < 4); //todo: swap with MAX_CONTROLLERS
    return;
}

void osWritebackDCacheAll() {
    return;
}

void bzero(s8* arg0, u32 arg1) {
    u32 uVar1;

    if (arg1 == 0) {
        return;
    }
    uVar1 = arg1 >> 3;
    if (uVar1 != 0) {
        do {
            *arg0 = 0;
            arg0[1] = 0;
            arg0[2] = 0;
            arg0[3] = 0;
            arg0[4] = 0;
            arg0[5] = 0;
            arg0[6] = 0;
            arg0[7] = 0;
            arg0 += 8;
            --uVar1;
        } while (uVar1 != 0);
        arg1 = arg1 & 7;
        if (arg1 == 0) {
            return;
        }
    }
    do {
        *arg0 = 0;
        ++arg0;
        --arg1;
    } while (arg1 != 0);
    return;
}

void osViSetSpecialFeatures(u32 func) {
    return;
}

int osGetCount(void) {
    s32 extraout_r4;
    s64 lVar1 = OSGetTime();
    __div2i((int)((u64)(lVar1 * 0x2cb4178) >> 0x20), (int)(lVar1 * 0x2cb4178), 0, 40500000);
    return extraout_r4;
}

int fn_800105b8(void) {
    return;
}

int fn_800105bc(void) {
    return 0;
}