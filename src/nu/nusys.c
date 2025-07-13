#include <types.h>
#include <dolphin/os/OSAlloc.h>

int lbl_801bcad8 = 0;
OSHeapHandle lbl_800f30c0;
OSHeapHandle lbl_800f30c4;
Mtx lbl_801bca94;
Mtx lbl_800f31f4;
Mtx lbl_800f3274;

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
    lbl_800f30dc = &lbl_800bde00;
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

void fn_8000c5b8(code* param_1) {
    lbl_801bcad8 = 1;
    while (lbl_801bcad8 != 0) {
        (*param_1)(0);
    }
}

//void fn_8000c61c(int *param_1,int *param_2)

//void fn_8000c6a0(int param_1)

//int fn_8000ca60(void)

//void fn_8000cbec(uint *param_1)

void osWritebackDCacheAll() {
    return;
}

void osViSetSpecialFeatures(u32 func) {
    return;
}

int osGetCount(void) {
    undefined4 extraout_r4;
    longlong lVar1 = OSGetTime();
    __div2i((int)((ulonglong)(lVar1 * 0x2cb4178) >> 0x20), (int)(lVar1 * 0x2cb4178), 0, 40500000);
    return extraout_r4;
}

int fn_800105b8(void) {
    return;
}

int fn_800105bc(void) {
    return 0;
}