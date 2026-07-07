#include <types.h>

// threads!

s32 lbl_801D53C0;

s32 lbl_801D73C0;
s32 lbl_801D73C4; //mc
s32 lbl_801D73C8; //dvd

s32 threadGameNo;
s32 threadBuffer;
s32 threadResult;
s32 threadFirstFlag;

extern s32 lbl_801D96F0;
s32 lbl_801D9A18;
s32 lbl_801D9A1C;

s32 lbl_801D53C0;

s32 fn_800158C4(void) {
    if (lbl_801D53C0 == 0) {
        if (threadFirstFlag == 0) {
            return 0x24;
        }
        else {
            if (OSIsThreadTerminated(&threadFirstFlag) == 0) {
                return 0x24;
            }
            return lbl_801D9A18;
        }
    }
    else if (lbl_801D9A1C == 0) {
        return 0x24;
    }
    else {
        if (OSIsThreadTerminated(&lbl_801D96F0) == 0) {
            return 0x24;
        }
        return lbl_801D9A18;
    }
    return 0;
}

//gc thread dvd read
void fn_80015970(void) {
    threadResult = fn_800143C0(threadGameNo, threadBuffer);
    return;
}

s32 fn_800159B0(s32 arg0, s32 arg1) {
    if ((threadFirstFlag == 0) || (OSIsThreadTerminated(&lbl_801D73C8) != 0)) {
        lbl_801D53C0 = 0;
        threadResult = 0x24;
        threadGameNo = arg0;
        threadBuffer = arg1;
        if (OSCreateThread(&lbl_801D73C8, fn_80015970, 0, &lbl_801D73C8, 0x2000, 0x12, 1) == 0) {
            return 0x23;
        }
        else {
            OSResumeThread(&lbl_801D73C8);
            threadFirstFlag = 1;
            return 0x21;
        }
    }
    else {
        return 0x22;
    }
    return 0x0;
}

//gc thread memcard save
void fn_80015A8C(void) {
    threadResult = fn_80013AEC(threadGameNo, threadBuffer);
    return;
}

s32 fn_80015ACC(s32 arg0, s32 arg1) {
    if ((threadFirstFlag == 0) || (OSIsThreadTerminated(&lbl_801D73C4) != 0)) {
        lbl_801D53C0 = 0;
        threadResult = 0x24;
        threadGameNo = arg0;
        threadBuffer = arg1;
        if (OSCreateThread(&lbl_801D73C8, fn_80015A8C, 0, &lbl_801D73C4, 0x2000, 0x12, 1) == 0) {
            return 0x23;
        }
        else {
            OSResumeThread(&lbl_801D73C4);
            threadFirstFlag = 1;
            return 0x21;
        }
    }
    else {
        return 0x22;
    }
    return 0x0;
}

void fn_80015BA8(void) {
    s32 uVar1;
    int iVar2;
    int iVar4;

    uVar1 = threadGameNo;
    //gc_memoryCard_pullFlag = NULL;
    iVar2 = gc_memoryCard_mount(threadGameNo);
    if ((iVar2 == 0) || (iVar2 - 4U < 2)) {
        do {
            iVar2 = gc_memoryCard_errorCheck(CARDFormat(uVar1), "CARDFormat");
        } while (iVar2 == 0x12);
    }
    do {
        iVar4 = gc_memoryCard_errorCheck(CARDUnmount(uVar1), "CARDUnmount");
    } while (iVar4 == 0x12);
    if (iVar4 == 2) {
        iVar4 = 0;
    }
    if (iVar2 != 0) {
        iVar4 = iVar2;
    }
    threadResult = iVar4;
    return;
}

s32 fn_80015C80(s32 arg0) {
    if ((threadFirstFlag == 0) || (OSIsThreadTerminated(&lbl_801D73C4) != 0)) {
        lbl_801D53C0 = 0;
        threadResult = 0x24;
        threadGameNo = arg0;
        if (OSCreateThread(&lbl_801D73C4, fn_80015BA8, 0, &lbl_801D73C4, 0x2000, 0x12, 1) == 0) {
            return 0x23;
        }
        else {
            OSResumeThread(&lbl_801D73C4);
            threadFirstFlag = 1;
            return 0x21;
        }
    }
    else {
        return 0x22;
    }
    return 0;
}

void fn_80015D4C(void) {
    threadResult = gc_memoryCardDelete(1);
    return;
}

s32 fn_80015D78(void) {
    if ((threadFirstFlag == 0) || (OSIsThreadTerminated(&lbl_801D73C8) != 0)) {
        lbl_801D53C0 = 0;
        threadResult = 0x24;
        if (OSCreateThread(&lbl_801D73C8, fn_80015D4C, 0, &lbl_801D73C8, 0x2000, 0x12, 1) == 0) {
            return 0x23;
        }
        else {
            OSResumeThread(&lbl_801D73C8);
            threadFirstFlag = 1;
            return 0x21;
        }
    }
    else {
        return 0x22;
    }
    return 0x0;
}

extern s32 lbl_801EB088;
extern s32 lbl_801EB0B0;

extern s32 threadFirstFlag;
extern u32 lbl_801D9A0C;
extern u32 lbl_801D9A10;
extern u32 lbl_801D9A14;
//extern u32 lbl_801D9A18;
extern u32 lbl_801D9A20;
extern u32 lbl_801D9A24;

void fn_80015E30(void) {
    OSResumeThread(lbl_801EB0B0);
    if (lbl_801D9A0C != 0) {
        OSResumeThread();
    }
    return;
}

void fn_80015E74(void) {
    OSSetAlarm(&lbl_801EB088, 0x140000, 0, 0x13C680, fn_80015E30);
    lbl_801EB0B0 = OSGetCurrentThread();
    if (lbl_801D9A0C != 0) {
        OSSuspendThread();
    }
    OSSuspendThread(lbl_801EB0B0);
    return;
}

void fn_80015EEC(void) {
    s32 local_10[3];

    lbl_801D9A14 = fn_80012584(lbl_801D9A10, lbl_801D9A14, lbl_801D9A20, lbl_801D9A24, local_10, 0);
    lbl_801D9A18 = local_10[0];
    return;
}

void fn_80015F44(void) {
    s32 local_c[2];

    lbl_801D9A14 = fn_80012584(lbl_801D9A10, lbl_801D9A14, lbl_801D9A20, lbl_801D9A24, local_c, 1);
    lbl_801D9A18 = local_c[0];
    return;
}

//todo fix types
u32 fn_80015F9C(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4) {
    if ((lbl_801D9A1C == 0) || (OSIsThreadTerminated(&lbl_801D96F0) != 0)) {
        lbl_801D53C0 = 1;
        lbl_801D9A18 = 0x24;
        lbl_801D9A0C = arg4;
        lbl_801D9A10 = arg0;
        lbl_801D9A14 = arg1;
        lbl_801D9A20 = arg2;
        lbl_801D9A24 = arg3;
        if (threadFirstFlag == 0) {
            if (OSCreateThread(&lbl_801D96F0, fn_80015EEC, 0, &lbl_801D96F0, 0x2000, 0x12, 1) == 0) {
                return 0x23;
            }
        }
        else {
            if (OSCreateThread(&lbl_801D96F0, fn_80015F44, 0, &lbl_801D96F0, 0x2000, 0x12, 1) == 0) {
                return 0x23;
            }
        }
        OSResumeThread(&lbl_801D96F0);
        lbl_801D9A1C = 1;
        return 0x21;
    }
    else {
        return 0x22;
    }
    return 0x0;
}

void fn_800160CC(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4) {
    threadFirstFlag = 0;
    fn_80015F9C(arg0, arg1, arg2, arg3, arg4);
    return;
}

s32 fn_800160FC(void) {
    return lbl_801D9A14;
}

//new source file here?

void fn_8001610C(void) {
    VIWaitForRetrace();
    return;
}

void fn_8001612C(s32 arg0) {
    switch (arg0) {
    case 0:
        GCHandover_write(10, 1);
        break;
    case 1:
        GCHandover_write(0xb, 1);
        break;
    case 2:
        GCHandover_write(0xc, 1);
        break;
    }
    if (((GCHandover_read(10) == 1) && (GCHandover_read(0xb) == 1)) &&
        (GCHandover_read(0xc) == 1)) {
        GCHandover_write(0xd, 1);
    }
    return;
}

//fn_800161D0 (error print)

//fn_80016474

//fn_800166AC

//..

//fn_80017358 (more pad conversion??)

