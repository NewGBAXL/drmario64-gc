//NOTICE: DO NOT ADD TO THIS FILE, IT WILL BE LATER MERGED WITH GC.H AND DOUBLEY LINKED WITH DRMARIO

#include <types.h>

int lbl_800BE198 = 0;

//memory card stuff
int lbl_801C13A0 = 0;
int lbl_801C13A8 = 0;

//dvd stuff ?
int lbl_801D96F0 = 0;
int lbl_801D9A18 = 0;
int lbl_801DAFFC = 0;

extern s32* gc_memoryCard_exi;

//void fn_800124A0(s32 /*SND_FXID*/ fid, u4 vol, u4 pan) {
//	sndFXStartEx(fix, vol, pan, 0);
//}

//prototype mismatch
void fn_800124A0(u32 fid, u8 vol, u8 pan) {
    sndFXStartEx(fid, vol, pan, 0);
    return;
}

void gc_soundSetOutputMode(u8 mode) {
    switch (mode) {
        case 0:
            sndOutputMode(0);
            OSSetSoundMode(0);
            GCHandover_write(9, 1);
            break;
        case 2:
            sndOutputMode(2);
            OSSetSoundMode(1);
            GCHandover_write(9, 2);
            break;
        case 1:
        default:
            sndOutputMode(1);
            OSSetSoundMode(1);
            GCHandover_write(9, 0);
            break;
	}
}

u8 fn_80012568(u8 arg0) {
    lbl_800BE198 = arg0;
    lbl_801DAFFC = 1;
    return 0;
}

/* int fn_80012584(u4 arg0, int arg1, int arg2, uint arg3, u4* arg4,
    int arg5) {
} */

u8 gc_GetDVDDrive(void) {
    u8 ret = 0;
    switch (DVDGetDriveStatus()) {
    case -1:
        ret = 0x18;
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
    default:
        ret = 0x0;
        break;
    }
    return ret;
}

void gc_gcInit(void) {
    DVDInit();
    CARDInit();
}

/* s32 fn_800128E8(void) {
} */

u8 gc_memoryCard_errorCheck(int code, char* name) {
    switch (code) { //byte casting?
    case -128:
		return 0x3;
    case -2:
        return 0x6;
    case -3:
		return 0x2;
    case -1:
		return 0x12;
	case -5:
		return 0x11;
	case -6:
		return 0x5;
	case -13:
		return 0x4;
	case 0:
		return 0x0;
	case -10:
		return 0xa;
    case -11:
        return 0xb;
	case -14:
		return 0xc;
	case -4:
		return 0x9;
	case -7:
		return 0xd;
	case -8:
		return 0xe;
	case -9:
        return 0xf;
	case -12:
		return 0x10;
    default:
		return 0x1;
    }
}

u8 gc_memoryCard_pullFlag(void) {
    lbl_801C13A8 = 1;
    return 0;
}

//mount the memory card
void gc_memoryCard_mount(int chan) {
    int iVar1;
    u8 uVar2;
    if (fn_8001337c() == 0) {
        do {
            uVar2 = CARDMount(chan, chan * 0xa000 + -0x7fe3ec40, gc_memoryCard_pullFlag ); //fix struct
            iVar1 = gc_memoryCard_errorCheck(uVar2, "CARDMount");
        } while (iVar1 == 0x12);
        if (((iVar1 == 0) || (iVar1 == 5)) || (iVar1 == 4)) {
            do {
                iVar1 = gc_memoryCard_errorCheck(CARDCheck(chan), "CARDCheck");
            } while (iVar1 == 0x12);
        }
    }
    return;
}

s32 lbl_801C13A4; //fix later
s32 DAT_801C13A4; //this too

//probe the memory card
int fn_8001337C(u8 chan) {
    u8 uVar1;
    int iVar2;
    s32 auStack_14[8];

    do {
        uVar1 = CARDProbeEx(chan, auStack_14, &lbl_801C13A4);
        iVar2 = gc_memoryCard_errorCheck(uVar1, "CARDProbeEx");
    } while (iVar2 == 0x12);
    if ((iVar2 == 0) && (DAT_801C13A4 != 0x2000)) {
        iVar2 = 8;
    }
    return iVar2;
}

void gc_memoryCardChange_slot(s32* val) {
    gc_memoryCard_exi = val;
}

int gc_memoryCardFormat(u8 chan) {
    int iVar1 = 0;
    s32 uVar2;
    int iVar3;

    lbl_801C13A8 = 0;
    //iVar1 = fn_800132A8(); //CARDMount
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
/* int fn_800134C4(u4 arg0,u4 arg1,uint arg2) {
}*/

//create save data
/*u8 fn_80013694(int arg0) {
    memcpy(arg0, &lbl_8006b1c0, 0x40);
    memcpy(arg0 + 0x40, &save_banner, 0xc00);
    memcpy(arg0 + 0xc40, &lbl_8006cd50, 0x200);
    memcpy(arg0 + 0xe40, &lbl_8006b350, 0x400);
    memcpy(arg0 + 0x1240, &lbl_8006b950, 0x400);
    memcpy(arg0 + 0x1640, &lbl_8006bd50, 0x400);
    memcpy(arg0 + 0x1a40, &lbl_8006b750, 0x200);
    return 0x1c40;
}*/

/* void fn_80013748(int arg0) {
}*/

//..

extern s32* memoryCard_comment;
extern s32* TEX_banner;
extern s32* TLU_banner;
extern s32* TLU_banner;
extern s32* TEX_icon0;
extern s32* TEX_icon1;
extern s32* TEX_icon2;
extern s32* TLU_icon0;

//the struct is much bigger than just these
s32 gc_memoryCardStatus_set(s32 arg0) {
    memcpy(arg0, &memoryCard_comment, 0x40);
    memcpy(arg0 + 0x40, &TEX_banner, 0xc00);
    memcpy(arg0 + 0xc40, &TLU_banner, 0x200);
    memcpy(arg0 + 0xe40, &TEX_icon0, 0x400);
    memcpy(arg0 + 0x1240, &TEX_icon1, 0x400);
    memcpy(arg0 + 0x1640, &TEX_icon2, 0x400);
    memcpy(arg0 + 0x1a40, &TLU_icon0, 0x200);
    return 0x1c40;
}

/*void gc_memoryCardGet_status(int arg0) {
    *(s32*)(arg0 + 0x38) = 0;
    *(s32*)(arg0 + 0x30) = 0x40;
    *(byte*)(arg0 + 0x2e) = *(byte*)(arg0 + 0x2e) & 0xfc | 1;
    *(ushort*)(arg0 + 0x34) = *(ushort*)(arg0 + 0x34) & 0xfffc | 1;
    *(ushort*)(arg0 + 0x34) = *(ushort*)(arg0 + 0x34) & 0xfff3 | 4;
    *(ushort*)(arg0 + 0x34) = *(ushort*)(arg0 + 0x34) & 0xffcf | 0x10;
    *(ushort*)(arg0 + 0x34) = *(ushort*)(arg0 + 0x34) & 0xff3f | 0x40;
    *(ushort*)(arg0 + 0x34) = *(ushort*)(arg0 + 0x34) & 0xfcff | 0x100;
    *(ushort*)(arg0 + 0x34) = *(ushort*)(arg0 + 0x34) & 0xf3ff | 0x400;
    *(ushort*)(arg0 + 0x34) = *(ushort*)(arg0 + 0x34) & 0xcfff | 0x1000;
    *(ushort*)(arg0 + 0x34) = *(ushort*)(arg0 + 0x34) & 0x3fff | 0x4000;
    *(ushort*)(arg0 + 0x36) = *(ushort*)(arg0 + 0x36) & 0xfffc | 3;
    *(ushort*)(arg0 + 0x36) = *(ushort*)(arg0 + 0x36) & 0xfff3 | 0xc;
    *(ushort*)(arg0 + 0x36) = *(ushort*)(arg0 + 0x36) & 0xffcf | 0x30;
    *(ushort*)(arg0 + 0x36) = *(ushort*)(arg0 + 0x36) & 0xff3f;
    *(ushort*)(arg0 + 0x36) = *(ushort*)(arg0 + 0x36) & 0xfcff;
    *(ushort*)(arg0 + 0x36) = *(ushort*)(arg0 + 0x36) & 0xf3ff;
    *(ushort*)(arg0 + 0x36) = *(ushort*)(arg0 + 0x36) & 0xcfff;
    *(ushort*)(arg0 + 0x36) = *(ushort*)(arg0 + 0x36) & 0x3fff;
    *(byte*)(arg0 + 0x2e) = *(byte*)(arg0 + 0x2e) & 0xfb;
    return;
}*/

//this function smells like inlining
/*int _gc_memoryCardWrite(s32 arg0, s32 arg1, int arg2, s32 arg3,
    s32 arg4, int arg5, s32 arg6) {
    int iVar1;
    s32 uVar2;
    int iVar3;
    undefined auStack_b0[108];
    undefined auStack_44[4];
    s32 local_40;

    if (gc_memoryCard_pullFlag != 0) {
        return 2;
    }
    if (gc_memoryCard_pullFlag == 0) {
        do {
            uVar2 = CARDOpen(gc_memoryCard_exi, arg0, auStack_44);
            iVar1 = gc_memoryCard_errorCheck(uVar2, s_CARDOpen_800be200);
        } while (iVar1 == 0x12);
    }
    else {
        iVar1 = 2;
    }
    if (iVar1 == 9) {
        if (gc_memoryCard_pullFlag == 0) {
            do {
                uVar2 = CARDCreate(gc_memoryCard_exi, arg0, arg2, auStack_44);
                iVar1 = gc_memoryCard_errorCheck(uVar2, s_CARDCreate_800be240);
            } while (iVar1 == 0x12);
        }
        else {
            iVar1 = 2;
        }
        if (iVar1 != 0) {
            return iVar1;
        }
    }
    if (iVar1 == 0) {
        gc_memoryCardGet_status(auStack_b0);
        if (arg2 != 0) {
            do {
                uVar2 = CARDWrite(auStack_44, arg1, arg2, arg3);
                iVar1 = gc_memoryCard_errorCheck(uVar2, s_CARDWrite_800be268);
            } while (iVar1 == 0x12);
            if (iVar1 != 0) goto LAB_800139e0;
        }
        if (arg5 != 0) {
            do {
                uVar2 = CARDWrite(auStack_44, arg4, arg5, arg6);
                iVar1 = gc_memoryCard_errorCheck(uVar2, s_CARDWrite_800be268);
            } while (iVar1 == 0x12);
            if (iVar1 != 0) goto LAB_800139e0;
        }
        do {
            uVar2 = CARDSetStatus(gc_memoryCard_exi, local_40, auStack_b0);
            iVar1 = gc_memoryCard_errorCheck(uVar2, s_CARDSetStatus_800be274);
        } while (iVar1 == 0x12);
    }
LAB_800139e0:
    do {
        uVar2 = CARDClose(auStack_44);
        iVar3 = gc_memoryCard_errorCheck(uVar2, s_CARDClose_800be20c);
    } while (iVar3 == 0x12);
    if (iVar1 == 0) {
        iVar1 = iVar3;
    }
    return iVar1;
}*/

extern lbl_801EB080;
extern lbl_801EB07C;

void fn_800153D8(void) {
    lbl_801EB080 = -1;
    lbl_801EB07C = -1;
    return;
}

void fn_800156A4(s32 arg0, s32 arg1) {
    s32* uVar1;
    uVar1 = gc_memoryCard_exi;
    fn_800153F0(0, arg0); //mc stuff
    arg1 = 2;
    gc_memoryCard_exi = uVar1;
    return;
}

s32 fn_80015700(s32 arg0) {
    switch (arg0) {
    case 0:
    case 3:
    case 4:
    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 0xb:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
        return 0;
    default:
        return 1;
    }
}

void gc_resetSystem(void) {
    OSResetSystem(0, 0, 1);
    return;
}

void gc_resetHotreset(BOOL forceMenu) {
    OSResetSystem(1, 0, forceMenu);
}

void fn_8001585C(void) {
    int iVar1;

    DVDCancelAll();
    OSCancelThread(&lbl_801D96F0);
    do {
        iVar1 = FUN_80048f50(&lbl_801D96F0);
    } while (iVar1 == 0);
    lbl_800BE198 = 0xfffffed4;
    lbl_801D9A18 = 0x25;
    return;
}

//..
