#include <types.h>
#include <dolphin/os/OSAlloc.h>
#include "libultra.h"
#include "nu/nusys.h"

int lbl_801BCAD8 = 0;
OSHeapHandle lbl_800F30C0;
OSHeapHandle lbl_800F30C4;
Mtx lbl_801BCA94;
Mtx lbl_800F31F4;
Mtx lbl_800F3274;

u32 lbl_800F3E5C;
u32 lbl_800F3E60;
u32 lbl_800F3FA0;
u32 lbl_800F3FA4;
u32 lbl_800F3FA8;
u32 lbl_800F3FAC;

extern lbl_8006A8F0;
extern lbl_8006A8F4;
extern lbl_8006a8f8;
extern lbl_8006a8c0;
extern lbl_8006a8fc;
extern lbl_800f3234;
extern lbl_800f30dc;
extern lbl_800bde00;

void GCNIS_nuGfxInit_relocate(void) {
    fn_8000bf24();
    OSSetCurrentHeap(lbl_800F30C0);
    if (OSCheckHeap(lbl_800F30C0) == -1) {
        NPC_ErrorPrint(0, "nusys.c", 0x18ab, "Heap Error", 0, 0, 0);
    }
    if (lbl_800F30C4 != lbl_800F30C0) {
        NPC_ErrorPrint(0, "nusys.c", 0x18ac, "Break! hCurrentHeap", 0, 0, 0);
    }
    PSMTXIdentity(&lbl_801BCA94);
    PSMTXIdentity(&lbl_800F31F4);
    PSMTXIdentity(&lbl_800F3274);
    C_MTXOrtho((double)lbl_8006A8F0, (double)lbl_8006A8F4, (double)lbl_8006A8F0, (double)lbl_8006a8f8,
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

void nuGfxFuncExit(void) {
    lbl_801BCAD8 = 0;
}

void nuGfxFuncSet(void(*arg0)(s32)) {
    lbl_801BCAD8 = 1;
    while (lbl_801BCAD8 != 0) {
        arg0(0);
    }
}

void fn_8000C61C(s8* arg0, s8* arg1) {
    arg1[0x0] = arg0[0x0];
    arg1[0x1] = arg0[0x4];
    arg1[0x2] = arg0[0x8];
    arg1[0x3] = arg0[0xc];
    arg1[0x4] = arg0[0x1];
    arg1[0x5] = arg0[0x5];
    arg1[0x6] = arg0[0x9];
    arg1[0x7] = arg0[0xd];
    arg1[0x8] = arg0[0x2];
    arg1[0x9] = arg0[0x6];
    arg1[0xa] = arg0[0xa];
    arg1[0xb] = arg0[0xe];
    arg1[0xc] = arg0[0x3];
    arg1[0xd] = arg0[0x7];
    arg1[0xe] = arg0[0xb];
    arg1[0xf] = arg0[0xf];
    return;
}

void fn_8000C618(int* arg0, int* arg1) {
    return;
}

//void fn_8000c61c(int *arg0,int *arg1)

extern s32 lbl_800F3E78;
extern s32 lbl_800F3E04;
extern s32 lbl_800F3E74;

int fn_8000CA60(void) {
    u32 uVar1;
    u32 uVar2;
    u8 bVar3;
    u8 bVar4;
    int iVar5;

    uVar2 = lbl_800F3FA0 >> 2;
    uVar1 = lbl_800F3FA4 >> 2;
    if ((uVar2 == 0) && (uVar1 == 0)) {
        return 0;
    }
    iVar5 = (*(u16*)(lbl_800F3E04 + 2) & 0xfff) + 1;
    if (iVar5 == 1) {
        iVar5 = (lbl_800F3FA8 - lbl_800F3FA0 >> 2) + 1;
    }
    bVar4 = *(u8*)((&lbl_800F3E78)[lbl_800F3E74] + 1) >> 3 & 3;
    bVar3 = *(u8*)((&lbl_800F3E78)[lbl_800F3E74] + 1) >> 5;
    if ((bVar4 == 1) && (bVar3 == 2)) {
        return uVar2 + uVar1 * iVar5;
    }
    if ((bVar4 == 0) && (bVar3 == 2)) {
        return uVar2 + uVar1 * iVar5;
    }
    if ((bVar4 == 0) && (bVar3 == 4)) {
        return uVar2 + uVar1 * iVar5;
    }
    if ((bVar4 == 0) && (bVar3 == 3)) {
        return uVar2 + uVar1 * iVar5;
    }
    if ((bVar4 == 1) && (bVar3 == 4)) {
        return uVar2 + uVar1 * iVar5;
    }
    if ((bVar4 == 1) && (bVar3 == 3)) {
        return uVar2 + uVar1 * iVar5;
    }
    if ((bVar4 == 2) && (bVar3 == 3)) {
        return (uVar2 + uVar1 * iVar5) * 2;
    }
    if ((bVar4 == 2) && (bVar3 == 0)) {
        return (uVar2 + uVar1 * iVar5) * 2;
    }
    if ((bVar4 == 3) && (bVar3 == 0)) {
        return (uVar2 + uVar1 * iVar5) * 2;
    }
    return 0;
}

//int fn_8000ca60(void)

//the big microcode handler
//void fn_8000cbec(uint *arg0)

void fn_8000FAE4(void) {
    u8 uStack_37;
    u8 uStack_36;
    u8 auStack_35[17];
    u8 auStack_24[4];
    u8 auStack_20[4];
    u8 auStack_1c[4];
    u8 auStack_18[4];
    u8 auStack_14[4];
    u8 auStack_10[4];
    u8 auStack_c[4];
    u8 auStack_8[8];

    GXReadXfRasMetric(auStack_c, auStack_8, auStack_14, auStack_10);
    GXReadXfRasMetric(auStack_1c, auStack_18, auStack_24, auStack_20);
    GXGetGPStatus(&uStack_37, &uStack_37, auStack_35, &uStack_36, &uStack_37);
    return;
}

extern s8 lbl_801BCAE8; //local

void fn_8000FB40(s32 arg0) {
    lbl_801BCAE8 = arg0;
    return;
}

extern s8 lbl_801BCADC; //local
extern s32 lbl_8022DB10;
extern s32 DemoCurrentBuffer;
extern s32 lbl_801BCAE0;
extern s32 lbl_801BCAE4;
extern s32 lbl_800F3FD0;

void fn_8000FB50(void* arg0) {
    bool bVar1;
    
    if (lbl_801BCADC != 0) {
        bVar1 = false;
        GXCopyDisp(DemoCurrentBuffer, 1);
        GXSetDrawSync(0xb00b);
        lbl_801BCAE0 = 0;
        while ((GXReadDrawSync() != -0x4ff5) && (!bVar1)) {
            if (lbl_801BCAE4 <= lbl_801BCAE0) {
                bVar1 = true;
                fn_8000FAE4();
                fn_8000F858(lbl_800F3FD0);
                fn_80054CD0(1);
            }
        }
        SwapBuffers();
    }
    else {
        if (lbl_8022DB10 != 0) {
            GXDrawDone();
            DEMOUpdateStats(1);
            DEMOPrintStats();
            GXDrawDone();
            DEMOUpdateStats(0);
        }
        GXSetZMode(1, 3, 1);
        GXSetColorUpdate(1);
        /*if (arg0 != (void*)0x0) {
            (*arg0)();
        }*/
        if (lbl_801BCAE8 == 0) {
            GXCopyDisp(DemoCurrentBuffer, 0);
        }
        else {
            GXCopyDisp(DemoCurrentBuffer, 1);
        }
        lbl_801BCAE8 = 0;
        GXDrawDone();
        SwapBuffers();
    }
    return;
}

extern s32 lbl_8006A8BC;
extern s32 lbl_8006A8D0;
extern s32 lbl_8006A8C0;

//setup viewport, possibly for error printing
void fn_8000FCBC(void) {
    if (lbl_801BCADC != 0) {
        GXSetDrawSync(0xfeeb);
        GXClearGPMetric();
    }
    if (*(u8*)(lbl_800F3FD0 + 0x18) != 0) {
        VIGetNextField();
        GXSetViewportJitter(lbl_8006A8BC, lbl_8006A8BC,
            (double)(float)((double)CONCAT44(0x43300000, (u32) * (u16*)(lbl_800F3FD0 + 4)) -
                lbl_8006A8D0),
            (double)(float)((double)CONCAT44(0x43300000, (u32) * (u16*)(lbl_800F3FD0 + 6)) -
                lbl_8006A8D0), lbl_8006A8BC, (double)lbl_8006A8C0);
    }
    else {
        GXSetViewport(lbl_8006A8BC, lbl_8006A8BC,
            (double)(float)((double)CONCAT44(0x43300000, (u32) * (u16*)(lbl_800F3FD0 + 4)) -
                lbl_8006A8D0),
            (double)(float)((double)CONCAT44(0x43300000, (u32) * (u16*)(lbl_800F3FD0 + 6)) -
                lbl_8006A8D0), lbl_8006A8BC, (double)lbl_8006A8C0);
    }
    GXInvalidateVtxCache();
    GXInvalidateTexAll();
    return;
}

void nuGfxTaskStart(void) {
    s32 unused;
    nuGfxTaskStart2();
    return;
}

void nuGfxRetraceWait(void) {
    s32 uVar1;
    s32 uVar2;

    uVar1 = VISetPreRetraceCallback(0);
    uVar2 = VISetPostRetraceCallback(0);
    VIWaitForRetrace();
    VISetPreRetraceCallback(uVar1);
    VISetPostRetraceCallback(uVar2);
    return;
}

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


void nuContDataGetExAll(NUContData* contdata) {
    u32 iVar1;
    u8 uVar2;

    iVar1 = NPC_GetPad(0);
    /*uVar2 = 0;NPC_PADtoN64(*(undefined2*)(iVar1 + 4));
    *contdata = uVar2;
    *(undefined*)(contdata + 1) = *(undefined*)(iVar1 + 10);
    *(undefined*)((int)contdata + 3) = *(undefined*)(iVar1 + 0xb);
    *(undefined*)(contdata + 2) = 0;
    uVar2 = NPC_PADtoN64(*(undefined2*)(iVar1 + 6));
    contdata[3] = uVar2;*/
    /*iVar1 = NPC_GetPad(1);
    uVar2 = NPC_PADtoN64(*(undefined2*)(iVar1 + 4));
    contdata[4] = uVar2;
    *(undefined*)(contdata + 5) = *(undefined*)(iVar1 + 10);
    *(undefined*)((int)contdata + 0xb) = *(undefined*)(iVar1 + 0xb);
    *(undefined*)(contdata + 6) = 0;
    uVar2 = NPC_PADtoN64(*(undefined2*)(iVar1 + 6));
    contdata[7] = uVar2;
    iVar1 = NPC_GetPad(2);
    uVar2 = NPC_PADtoN64(*(undefined2*)(iVar1 + 4));
    contdata[8] = uVar2;
    *(undefined*)(contdata + 9) = *(undefined*)(iVar1 + 10);
    *(undefined*)((int)contdata + 0x13) = *(undefined*)(iVar1 + 0xb);
    *(undefined*)(contdata + 10) = 0;
    uVar2 = NPC_PADtoN64(*(undefined2*)(iVar1 + 6));
    contdata[0xb] = uVar2;
    iVar1 = NPC_GetPad(3);
    uVar2 = NPC_PADtoN64(*(undefined2*)(iVar1 + 4));
    contdata[0xc] = uVar2;
    *(undefined*)(contdata + 0xd) = *(undefined*)(iVar1 + 10);
    *(undefined*)((int)contdata + 0x1b) = *(undefined*)(iVar1 + 0xb);
    *(undefined*)(contdata + 0xe) = 0;
    uVar2 = NPC_PADtoN64(*(undefined2*)(iVar1 + 6));
    contdata[0xf] = uVar2;*/
    return;
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
            arg0[0] = 0;
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
        arg1 &= 7;
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


void bcopy(s32* arg0, s32* arg1, u32 arg2) {
    s32* puVar1;
    u8 uVar2;
    u32 uVar3;

    if (arg2 == 0) {
        return;
    }
    uVar3 = arg2 >> 3;
    if (uVar3 != 0) {
        do {
            arg1[0] = arg0[0];
            arg1[1] = arg0[1];
            arg1[2] = arg0[2];
            arg1[3] = arg0[3];
            arg1[4] = arg0[4];
            arg1[5] = arg0[5];
            arg1[6] = arg0[6];
            puVar1 = arg0 + 7;
            arg0 += 8;
            arg1[7] = *puVar1;
            arg1 += 8;
            uVar3 -= 1;
        } while (uVar3 != 0);
        arg2 &= 7;
        if (arg2 == 0) {
            return;
        }
    }
    do {
        uVar2 = *arg0;
        arg0 += 1;
        *arg1 = uVar2;
        arg1 += 1;
        arg2 -= 1;
    } while (arg2 != 0);
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

int fn_800105B8(void) {
    return;
}

int fn_800105BC(void) {
    return 0;
}

//whatever this does..
void fn_800105C4(s32 arg0, s32 arg1) {
    lbl_800F3E5C = ((u32)(lbl_800F3FA8 - lbl_800F3FA0) >> 2) + 1;
    lbl_800F3E60 = ((u32)(lbl_800F3FAC - lbl_800F3FA4) >> 2) + 1;
    fn_80007ACC(arg0, lbl_800F3E5C, lbl_800F3E60, arg1);
    return;
}

//...

extern s32 lbl_800F30C8;
extern s32 lbl_800F30CC;

int fn_80010D00(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
    s32 arg4, s32 arg5, s32 arg6, s32 arg7,
    s32 arg8, s32 arg9) {
    int iVar1;

    iVar1 = fn_80010A74(arg0, arg6, arg7);
    if (iVar1 == 0) {
        iVar1 = fn_80010B88(arg0, arg6, arg7);
        fn_8000A618(iVar1, arg0, arg1, arg2, arg3, arg6, arg7, arg8, arg9);
        DCFlushRange(iVar1, 0x1400);
        lbl_800F30C8 += 1;
    }
    else {
        lbl_800F30CC += 1;
    }
    return iVar1;
}

extern void* lbl_800F4024; //todo

void fn_80010EA8(void) {
    s32 iVar1;
    void* puVar2;

    iVar1 = 0;
    puVar2 = lbl_800F4024;
    do {
        OSFreeToHeap(__OSCurrHeap, puVar2);
        ++iVar1;
        //*puVar2 = 0;
        //++puVar2;
    } while (iVar1 < 0x26a);
    return;
}
