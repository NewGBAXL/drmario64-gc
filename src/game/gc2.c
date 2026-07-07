#include <types.h>

//start some thread

s32 lbl_801F9C18;
extern s32 lbl_801FDF30;

void fn_80019774();

void fn_8001970C(void) {
    if (OSIsThreadTerminated(&lbl_801F9C18) != 0) {
        OSCreateThread(&lbl_801F9C18, fn_80019774, 0, &lbl_801FDF30, 0x1000, 0x1e, 1);
        OSResumeThread(&lbl_801F9C18);
    }
    return;
}

void fn_80019774() {}

//extern s32 resetFlag; //mc cnt?

s32 resetFlag;

void fn_800198F8(void) {
    int iVar1;

    if (resetFlag == 2) {
        do {
            do {
            } while (CARDCheck(0) == -1);
        } while (CARDCheck(1) == -1);
        VISetBlack(1);
        VIFlush();
        GXAbortFrame();
        GXDrawDone();
        VIWaitForRetrace();
        gc_resetSystem();
    }
    return;
}

void fn_80019960(void) {
    VISetBlack(1);
    VIFlush();
    GXAbortFrame();
    GXDrawDone();
    VIWaitForRetrace();
    return;
}

s32 gc_GetResetFlag(void) {
    return resetFlag;
}

//extern s32 lbl_801FDF30;
extern s32 lbl_801FDF34;
extern s32 lbl_801FDF38;
extern s32 lbl_801FDF3C;
extern s32 lbl_801FDF40;
extern s32 lbl_801FDF44;
extern s32 lbl_801FDF48;
extern s32 lbl_801FDF4C;
extern s32 lbl_801FDF50;
extern s32 lbl_801FDF54;
extern s32 lbl_801FDF58;
extern s32 lbl_801FDF5C;

void gc_PutResetNone(void) {
    resetFlag = 0;
    lbl_801FDF30 = 0;
    lbl_801FDF44 = 0;
    lbl_801FDF40 = 0;
    lbl_801FDF34 = 0;
    lbl_801FDF4C = 0;
    lbl_801FDF48 = 0;
    lbl_801FDF38 = 0;
    lbl_801FDF54 = 0;
    lbl_801FDF50 = 0;
    lbl_801FDF3C = 0;
    lbl_801FDF5C = 0;
    lbl_801FDF58 = 0;
    return;
}

extern s32 lbl_801FDF60;

s32 fn_800199E4(void) {
    int iVar1;

    iVar1 = OSGetResetButtonState();
    if ((lbl_801FDF60 != 0) && (iVar1 == 0)) {
        lbl_801FDF60 = 0;
        if (gc_GetDVDDrive() != 0x18) {
            return 1;
        }
    }
    lbl_801FDF60 = iVar1;
    return 0;
}


u32 fn_80019A58(void) {
    int extraout_r4;
    s32 uVar2; //long?
    u16 local_84;
    s8 auStack_7c[4];
    u16 local_78;

    local_78 = 0;
    fn_800179D8(auStack_7c, 0);
    if (fn_8004D9BC(0) == 0x40000) {
        local_84 = 0x1310;
    }
    else {
        local_84 = 0x1600;
    }
    /*if (((local_78 & 0xfff0) == local_84) && fn_80019C1C() != 0)) {
        if (lbl_801FDF30 == 0) {
            lbl_801FDF30 = 1;
            uVar2 = OSGetTime();
        }
        else {
            OSGetTime();
            uVar2 = CONCAT44(lbl_801FDF40, lbl_801FDF44);
            if (499 < (uint)(extraout_r4 - lbl_801FDF44) / 0x9e34) {
                lbl_801FDF30 = 0;
                uVar2 = OSGetTime();
                lbl_801FDF40 = (s32)((ulonglong)uVar2 >> 0x20);
                lbl_801FDF44 = (int)uVar2;
                iVar1 = gc_GetDVDDrive();
                uVar2 = CONCAT44(lbl_801FDF40, lbl_801FDF44);
                if (iVar1 != 0x18) {
                    return 1;
                }
            }
        }
    }
    else {
        lbl_801FDF30 = 0;
        uVar2 = 0;
    }*/
    lbl_801FDF40 = (s32)((s64)uVar2 >> 0x20);
    lbl_801FDF44 = (int)uVar2;
    if (resetFlag != 0) {
        lbl_801FDF30 = 0;
    }
    return 0;
}

void fn_80019B88(void) {
    if (DVDCheckDisk() == 0) {
        VISetBlack(1);
        VIFlush();
        GXAbortFrame();
        GXDrawDone();
        VIWaitForRetrace();
        gc_resetHotreset(0);
    }
    return;
}

//umm is this what this is??
void gc_WaitForReset(void) {
    do {
    } while (PADRecalibrate(0xf0000000) == 0);
    do {
        do {
        } while (CARDCheck(0) == -1);
    } while (CARDCheck(1) == -1);
    return;
}

s32 lbl_800BE590;

s32 fn_80019C1C(void) {
    if (lbl_800BE590 != 0) {
        return 1;
    }
    else {
        if (gc_GetDVDDrive() != 0) {
            return 1;
        }
        else {
            return 0;
        }
    }
}

void fn_80019C68(void) {
    lbl_800BE590 = 0;
    return;
}

extern s32 lbl_801F9C10;

void fn_80019C78(void) {
    lbl_800BE590 = 1;
    lbl_801F9C10 = 0;
    lbl_801FDF30 = 0;
    lbl_801FDF44 = 0;
    lbl_801FDF40 = 0;
    lbl_801FDF34 = 0;
    lbl_801FDF4C = 0;
    lbl_801FDF48 = 0;
    lbl_801FDF38 = 0;
    lbl_801FDF54 = 0;
    lbl_801FDF50 = 0;
    lbl_801FDF3C = 0;
    lbl_801FDF5C = 0;
    lbl_801FDF58 = 0;
    return;
}

s32 fn_80019CC8(u8 arg0, u16* arg1) {
    s32* puVar1 = (s32*)fn_800179C4();
    *arg1 = *(s16*)(puVar1 + 1);
    return *puVar1;
}

//void fn_80019D00(void)

//void fn_8001A004(void* arg0)

void fn_8001A22C(void) {
    fn_8001A004(0);
    return;
}

void fn_8001A250(void) {
    GCNIS_nuGfxInit_relocate();
    return;
}

void fn_8001A270(void) {
    fn_80010EA8();
    return;
}

extern s32 lbl_80202078;
s32 lbl_8020207C;
extern s32 lbl_80202080;
extern s32 lbl_80202084;
extern s32 lbl_80202088;
s8 lbl_8020208C;
extern s32 lbl_80202090;
static void (*lbl_80202094)(void);

void fn_8001A290(void) {
    lbl_80202078 = 0;
    lbl_8020208C = 0;
    lbl_80202090 = 0;
    lbl_80202094 = 0;
    return;
}

void fn_8001A2B0(u32 arg0) {
    lbl_80202080 = arg0 >> 8 & 0xf8;
    lbl_80202084 = arg0 >> 3 & 0xf8;
    lbl_80202088 = (arg0 & 0x3e) << 2;
    lbl_8020208C = 0xff;
    lbl_80202078 = 2;
    return;
}

s32 fn_8001A2E4(void) {
    if (lbl_8020208C < 1) {
        lbl_8020208C = 0;
        return 1;
    }
    lbl_8020208C -= 8;
    if (-1 < lbl_8020208C) {
        return 0;
    }
    lbl_8020208C = 0;
    return 0;
}

s32 fn_8001A32C(void) {
    s32 uVar1;

    uVar1 = 0;
    if (lbl_8020208C < -1) {
        lbl_8020208C += 8;
        if (-1 < lbl_8020208C) {
            lbl_8020208C = -1;
        }
    }
    else {
        lbl_8020208C = -1;
        if (lbl_80202094 != NULL) {
            (*lbl_80202094)();
            lbl_80202094 = NULL;
        }
        if (lbl_80202090 < 1) {
            uVar1 = 1;
        }
        else {
            lbl_80202090 -= 1;
        }
    }
    return uVar1;
}

void fn_8001A3D4(void) {
    if (lbl_80202090 < 0) {
        lbl_80202078 = 1;
        return;
    }
    else {
        lbl_8020207C = 1;
        return;
    }
}

void fn_8001A400(u32 arg0, s32 arg1, s32 arg2) {
    lbl_8020207C = 0;
    lbl_80202078 = 2;
    lbl_80202080 = arg0 >> 8 & 0xf8;
    lbl_80202084 = arg0 >> 3 & 0xf8;
    lbl_80202088 = (arg0 & 0x3e) << 2;
    lbl_80202090 = arg1;
    //lbl_80202094 = arg1;
    return;
}

//inlining here??
void fn_8001A43C(u32 arg0, s32 arg1, s32 arg2) {
    lbl_8020207C = 0;
    lbl_80202078 = 2;
    lbl_80202080 = arg0 >> 8 & 0xf8;
    lbl_80202084 = arg0 >> 3 & 0xf8;
    lbl_80202088 = (arg0 & 0x3e) << 2;
    lbl_80202090 = arg1;
    //lbl_80202094 = arg1;
    if (arg1 < 0) {
        lbl_80202078 = 1;
        return;
    }
    else {
        lbl_8020207C = 1;
        return;
    }
}

u32 fn_8001A494(void) {
    u32 uVar1;

    if (lbl_80202078 == 1) {
        if (lbl_8020208C == 0) {
            return 1;
        }
        return 0;
    }
    if (lbl_80202078 != 2 || lbl_8020207C != 0) {
        return 1;
    }
    uVar1 = countLeadingZeros(0xff - lbl_8020208C);
    return uVar1 >> 5;
}

s32 fn_8001A4F0(void) {
    return lbl_80202078;
}
