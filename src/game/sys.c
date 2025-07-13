#include <types.h>

int lbl_800be198 = 0;

//memory card stuff
int lbl_801c13a0 = 0;
int lbl_801c13a8 = 0;

//dvd stuff ?
int lbl_801d96f0 = 0;
int lbl_801d9a18 = 0;
int lbl_801daffc = 0;

void fn_800124A0(SND_FXID fid, u4 vol, u4 pan) {
	sndFXStartEx(fix, vol, pan, 0);
}

void fn_800124C8(u8 mode) {
    switch (mode) {
        case 0:
            sndOutputMode(0);
            OSSetProgressiveMode(0);
            GCHandover_write(9, 1);
            break;
        case 1:
            sndOutputMode(1);
            OSSetProgressiveMode(1);
            GCHandover_write(9, 0);
            break;
        case 2:
            sndOutputMode(2);
            OSSetProgressiveMode(1);
            GCHandover_write(9, 2);
            break;
        default:
            break;
	}
}

u4 fn_80012568(u4 param_1) {
    lbl_800be198 = param_1;
    lbl_801daffc = 1;
    return 0;
}

/* int fn_80012584(u4 param_1, int param_2, int param_3, uint param_4, u4* param_5,
    int param_6) {
} */

u4 gc_GetDVDDrive(void) {
    int ret = 0;
    switch (DVDGetDriveStatus()) {
    default:
        ret = 0;
        break;
    case 4:
        ret = 0x1b;
        break;
    case 5:
        ret = 0x1c;
        break;
    case 6:
        ret = 0x1d;
        break;
    case 0xb:
        ret = 0x20;
        break;
    case 0xffffffff:
        ret = 0x18;
    }
    return ret;
}

void fn_800128C4(void) {
    DVDInit();
    CARDInit();
}

/* undefined4 fn_800128E8(void) {
} */

u4 gc_memoryCard_errorCheck(int code, char* name) {
    switch (code) { //byte casting?
    case 0:
		return 0;
    case -1:
        return 18;
    case -2:
		return 6;
    case -3:
		return 2;
	case -4:
		return 9;
	case -5:
		return 17;
	case -6:
		return 5;
	case -7:
		return 13;
	case -8:
		return 14;
	case -10:
		return 10;
	case -11:
		return 15;
	case -12:
		return 11;
	case -13:
		return 4;
	case -14:
        return 12;
	case -128:
		return 3;
	default:
		return 1;
    }
}

u4 fn_80013294(void) {
    lbl_801c13a8 = 1;
    return 0;
}

//mount the memory card
void fn_800132A8(int chan) {
    int iVar1;
    u4 uVar2;
    if (fn_8001337c() == 0) {
        do {
            uVar2 = CARDMount(chan, chan * 0xa000 + -0x7fe3ec40, fn_80013294); //fix struct
            iVar1 = gc_memoryCard_errorCheck(uVar2, "CARDMount");
        } while (iVar1 == 0x12);
        if (((iVar1 == 0) || (iVar1 == 5)) || (iVar1 == 4)) {
            do {
                iVar1 = gc_memoryCard_errorCheck(CARDCheck(param_1), s_CARDCheck_800BE1DC);
            } while (iVar1 == 0x12);
        }
    }
    return;
}

//probe the memory card
int fn_8001337C(u4 chan) {
    u4 uVar1;
    int iVar2;
    undefined auStack_14[8];

    do {
        uVar1 = CARDProbeEx(chan, auStack_14, &lbl_801c13a4);
        iVar2 = gc_memoryCard_errorCheck(uVar1, "CARDProbeEx");
    } while (iVar2 == 0x12);
    if ((iVar2 == 0) && (DAT_801c13a4 != 0x2000)) {
        iVar2 = 8;
    }
    return iVar2;
}

void fn_80013400(u4 val) {
    lbl_801c13a0 = val;
}

//format the memory card
int fn_8001340C(u4 chan) {
    int iVar1;
    undefined4 uVar2;
    int iVar3;

    lbl_801c13a8 = 0;
    iVar1 = fn_800132A8(); //CARDMount
    if ((iVar1 == 0) || (iVar1 - 4U < 2)) {
        do {
            iVar1 = gc_memoryCard_errorCheck(CARDFormat(chan), "CARDFormat");
        } while (iVar1 == 0x12);
    }
    do {
        iVar3 = gc_memoryCard_errorCheck(CARDUnmount(chan), "CARDUnmount");
    } while (iVar3 == 0x12);
    if (iVar3 == 2) {
        iVar3 = 0;
    }
    if (iVar1 != 0) {
        iVar3 = iVar1;
    }
    return iVar3;
}

//check free space on the memory card
/* int fn_800134C4(u4 param_1,u4 param_2,uint param_3) {
}*/

//create save data
u4 fn_80013694(int param_1) {
    memcpy(param_1, &lbl_8006b1c0, 0x40);
    memcpy(param_1 + 0x40, &save_banner, 0xc00);
    memcpy(param_1 + 0xc40, &lbl_8006cd50, 0x200);
    memcpy(param_1 + 0xe40, &lbl_8006b350, 0x400);
    memcpy(param_1 + 0x1240, &lbl_8006b950, 0x400);
    memcpy(param_1 + 0x1640, &lbl_8006bd50, 0x400);
    memcpy(param_1 + 0x1a40, &lbl_8006b750, 0x200);
    return 0x1c40;
}

/* void fn_80013748(int param_1) {
}*/

//..

void fn_80015830(BOOL forceMenu) {
    OSResetSystem(1, 0, forceMenu);
}

void fn_8001585C(void) {
    int iVar1;

    DVDCancelAll();
    OSCancelThread(&lbl_801d96f0);
    do {
        iVar1 = FUN_80048f50(&lbl_801d96f0);
    } while (iVar1 == 0);
    lbl_800be198 = 0xfffffed4;
    lbl_801d9a18 = 0x25;
    return;
}

//..
