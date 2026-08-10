#include <types.h>

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
