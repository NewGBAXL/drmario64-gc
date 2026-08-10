//START FILE 1

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

//START FILE 2 - lbl_801EB0B0 bss

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

//BACK TO FILE 1?

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

//START FILE 3

void fn_800160CC(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4) {
    threadFirstFlag = 0;
    fn_80015F9C(arg0, arg1, arg2, arg3, arg4);
    return;
}

//START FILE 4 - lbl_801D9A14 bss

s32 fn_800160FC(void) {
    return lbl_801D9A14;
}

//new source file here?

void fn_8001610C(void) {
    VIWaitForRetrace();
    return;
}

void GCHandover_write(s32 arg0, u8 arg1);
u8 GCHandover_read(s32 arg0);

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

//START FILE 6 - lbl_800BE198 bss

//fn_800161D0 (error print)

//fn_80016474

//fn_800166AC

//..

//fn_80017358 (more pad conversion??)

//new stuff

extern s32 lbl_801EB2B8;
extern s32 lbl_801EB2BC;
extern s32 lbl_801EB2BE;
extern s32 lbl_801EB2C0;

//fn_80017528 //NPC_Readpads

s32* fn_800179C4(int num) { //NPC_GetPad
    return &lbl_801EB2B8 + num * 6;
}

u8 fn_800179D8(s32* arg0, int arg1) {
    u8 bVar1 = (&lbl_801EB2B8)[arg1 * 6] != 0;
    if (bVar1) {
        if (bVar1) {
            *arg0 = 1;
            *(u16*)(arg0 + 1) = *(u16*)(arg0 + 1) | (&lbl_801EB2BC)[arg1 * 0xc];
            *(u16*)((int)arg0 + 6) = *(u16*)((int)arg0 + 6) | (&lbl_801EB2BE)[arg1 * 0xc];
            *(u16*)(arg0 + 2) = *(u16*)(arg0 + 2) | (&lbl_801EB2C0)[arg1 * 0xc];
        }
        return bVar1;
    }
    return 0;
}

extern s32 lbl_801F5AC8;

extern s32 lbl_801EB318;

extern s32 lbl_801EB65C;

extern s32 lbl_801F5A70;

extern s32 lbl_800BE3D0;

void fn_80017A48(int arg0, int arg1) {
    u32 iVar1;

    *(s32*)(&lbl_800BE3D0 + arg0) = 0;
    iVar1 = (&lbl_801EB65C)[arg0];
    if (iVar1 != 0) {
        *(int*)(iVar1 + 0x10) = arg1;
    }
    if (arg1 != 0) {
        return;
    }
    *(s32*)((&lbl_801EB65C)[arg0] + 0x28e4) = 2;
    return;
}

void fn_80017A94() {
    OSResumeThread(&lbl_801EB318);
    return;
}

void fn_80017ABC(void) {
    u8 bVar1;
    s32 extraout_r4;
    u32 uVar2;
    int iVar3;
    s32* piVar4;

    lbl_801F5AC8 = 1;
    do {
        piVar4 = &lbl_801EB65C;
        uVar2 = 0;
        bVar1 = 0;
        iVar3 = 0;
        do {
            if (*piVar4 != 0) {
                if (*(char*)(*piVar4 + 0xc) == 'd') {
                    bVar1 = 1;
                }
                fn_80016830(); //NPC_UpdateGBAPad();
                if (*(int*)(*piVar4 + 4) != 0) {
                    *(s32*)(*piVar4 + 4) = 0;
                    uVar2 = uVar2 | 0x80000000U >> iVar3;
                }
            }
            iVar3 += 1;
            piVar4 += 1;
        } while (iVar3 < 4);
        if ((uVar2 & 0xff) != 0) {
            PADReset();
        }
        fn_8003A8A0();
        if (bVar1) {
            fn_80049F6C(&lbl_801EB318, 2);
            OSYieldThread();
        }
        else {
            fn_80049F6C(&lbl_801EB318, 0x11);
            OSSetAlarm(&lbl_801F5A70, extraout_r4, 0, 0x13c680, fn_80017A94);
            OSSuspendThread(&lbl_801EB318);
        }
    } while (1);
}

//extern s32 lbl_801EB2B8; //top of file?

extern s32 lbl_801F5A9C;
extern s32 lbl_801F5AA0;
extern s32 lbl_801F5AA4;

void fn_80017BD4(void) {
    s32* r31 = (s32*)((u8*)&lbl_801EB2B8 + 0x10000);
    if (*(s32*)((u8*)r31 - 0x581c) != 0) {
        DoFree(*(s32*)((u8*)r31 - 0x581c));
    }
    if (*(s32*)((u8*)r31 - 0x5818) != 0) {
        DoFree(*(s32*)((u8*)r31 - 0x5818));
    }
    if (*(s32*)((u8*)r31 - 0x5814) != 0) {
        DoFree(*(s32*)((u8*)r31 - 0x5814));
    }
}

s32 lbl_801EB63C;
s32 lbl_801EB640;
s32 lbl_801EB64C;
//s32 lbl_801EB65C;
u32 lbl_801EB660;
u32 lbl_801EB664;
u32 lbl_801EB668;

s32 lbl_801F9BFC;

s32 fn_80017C3C(int arg0) {
    return *(s32*)((&lbl_801EB65C)[arg0] + 0x28e8);
}

void fn_80017C58(int arg0, s32 arg1) {
    *(s32*)((&lbl_801EB65C)[arg0] + 0x28e8) = arg1;
    return;
}

void fn_80017C74(s32 arg0) {
    *(s32*)(lbl_801EB660 + 0x28e8) = arg0;
    *(s32*)(lbl_801EB664 + 0x28e8) = arg0;
    *(s32*)(lbl_801EB668 + 0x28e8) = arg0;
    return;
}

s32 fn_80017E08(s32 arg0);

s32 fn_80017C98(void) {
    s32 uVar3 = 0;
    int iVar2 = 1;

    do {
        if (fn_80017E08(iVar2) != 0) {
            uVar3 = 1;
        }
        iVar2 += 1;
    } while (iVar2 < 4);
    return uVar3;
}




//end new stuff

s32 fn_80017CF0(void) {
    int iVar2;
    s32 uVar3;
    s32* piVar4;

    piVar4 = &lbl_801F9BFC;
    uVar3 = 0;
    iVar2 = 1;
    do {
        if ((fn_80017E08(iVar2) != 0) && (1 < *piVar4)) {
            uVar3 = 1;
        }
        iVar2 += 1;
        piVar4 += 1;
    } while (iVar2 < 4);
    return uVar3;
}

s32 fn_80017D6C(void) {
    int iVar1;
    int iVar2;
    u32 uVar3;
    u32* piVar4;

    piVar4 = &lbl_801EB660;
    uVar3 = 0;
    iVar2 = 1;
    do {
        if ((((fn_80017E08(iVar2) != 0) && (*piVar4 != 0)) && (*(int*)(*piVar4 + 0x28e4) == 1)) &&
            (GBAGetProcessStatus(iVar2, 0) == 2)) {
            uVar3 = 1;
        }
        iVar2 += 1;
        piVar4 += 1;
    } while (iVar2 < 4);
    return uVar3;
}

s32 fn_80017E08(s32 arg0) {
    return *(s32*)(&lbl_801EB63C + arg0);
}

void fn_80017E20(int arg0, s32 arg1) {
    *(s32*)(&lbl_801EB63C + arg0) = arg1;
    return;
}

void fn_80017E38(int arg0) {
    if (SIProbe() == 0x40000) {
        (&lbl_801EB64C)[arg0] = OSGetTick();
        *(s32*)(&lbl_801EB63C + arg0 * 4) = 1;
    }
    else {
        if (800 < (u32)(OSGetTick() - (&lbl_801EB64C)[arg0]) / 0x9e34) {
            (&lbl_801EB64C)[arg0] = OSGetTick();
            *(s32*)(&lbl_801EB63C + arg0 * 4) = 0;
        }
    }
    return;
}

void fn_80017EE4(int arg0) {
    int iVar1;
    u32* piVar2;
    s32* piVar3;
    char local_14[4];

    piVar3 = &lbl_801EB640;
    piVar2 = &lbl_801EB660;
    iVar1 = 1;
    do {
        if (arg0 == 1) {
            local_14[0] = 0;
            if ((*piVar3 != 0) && (GBAGetProcessStatus(iVar1, local_14), local_14[0] == 0))
                goto LAB_80017f6c;
        }
        else {
            if (0 < arg0) {
                return;
            }
            if (arg0 < 0) {
                return;
            }
        LAB_80017f6c:
            if (*piVar2 != 0) {
                *(s32*)(*piVar2 + 0x28e4) = arg0;
            }
        }
        iVar1 += 1;
        piVar3 += 1;
        piVar2 += 1;
    } while (iVar1 < 4);
    return;
}

void fn_80017FB0(void) {
    int iVar1;
    int iVar2;
    u32* piVar3;
    s32* piVar4;
    char local_18[8];

    piVar4 = &lbl_801EB640;
    piVar3 = &lbl_801EB660;
    iVar2 = 1;
    do {
        local_18[0] = '\0';
        if (((*piVar4 == 0) || ((local_18[0] == '\0' && (GBAGetProcessStatus(iVar2, local_18) == 0)))) && (*piVar3 != 0)) {
            *(s32*)(*piVar3 + 0x28e4) = 0;
        }
        iVar2 += 1;
        piVar4 += 1;
        piVar3 += 1;
    } while (iVar2 < 4);
    return;
}

s32 fn_80018060(s32 arg0) {
    u32 ptr = ((u32*)&lbl_801EB65C)[arg0];
    if (ptr == 0) {
        return 0;
    }
    if (*(s32*)(ptr + 0x28e4) != 1) {
        return 0;
    }
    return 1;
}

//same file as above

extern s32 lbl_801EB638;
extern s32 lbl_801EB644;
extern s32 lbl_801EB648;

extern s32 lbl_801F9ACC;

s32 fn_8001835C(s32* arg0);
u8 fn_800186C0(void);

//todo
s32 fn_80018094(void) {
    u8 bVar1;
    u32 uVar2;
    int iVar3;
    int iVar4;
    s32 local_18[3];

    iVar4 = 0;
    bVar1 = 0;
    if ((lbl_801EB660 != 0) && (*(int*)(lbl_801EB660 + 0x28e4) == 1)) {
        bVar1 = 1;
    }
    if ((bVar1) && (lbl_801EB640 == 0)) {
        iVar4 = 1;
    }
    bVar1 = 0;
    if ((lbl_801EB664 != 0) && (*(int*)(lbl_801EB664 + 0x28e4) == 1)) {
        bVar1 = 1;
    }
    if ((bVar1) && (lbl_801EB644 == 0)) {
        iVar4 = 1;
    }
    bVar1 = 0;
    if ((lbl_801EB668 != 0) && (*(int*)(lbl_801EB668 + 0x28e4) == 1)) {
        bVar1 = 1;
    }
    if ((bVar1) && (lbl_801EB648 == 0)) {
        iVar4 = 1;
    }
    uVar2 = lbl_801EB638;
    if (iVar4 == 0) {
        local_18[0] = 0;
        uVar2 = fn_8001835C(local_18) & 0xff;
        if ((local_18[0] != 0) && local_18[0] != fn_800186C0()) {
            lbl_801F9ACC = 1;
        }
        if (((int)uVar2 < (int)lbl_801EB638) && (lbl_801F9ACC == 0)) {
            if (lbl_801F9ACC == 0) {
                lbl_801F9ACC = 0;
                uVar2 = lbl_801EB638;
            }
            else {
                lbl_801EB638 = 0;
                iVar4 = 1;
                uVar2 = lbl_801EB638;
            }
        }
    }
    lbl_801EB638 = uVar2;
    return iVar4;
}

s32 fn_80018214(void) {
    s32 uVar1;

    uVar1 = 0;
    if (((lbl_801EB660 != 0) && (lbl_801EB640 != 0)) && (*(int*)(lbl_801EB660 + 0x28e4) == 1)) {
        uVar1 = 1;
    }
    if (((lbl_801EB664 != 0) && (lbl_801EB644 != 0)) && (*(int*)(lbl_801EB664 + 0x28e4) == 1)) {
        uVar1 = 1;
    }
    if (lbl_801EB668 == 0) {
        return uVar1;
    }
    if (lbl_801EB648 == 0) {
        return uVar1;
    }
    if (*(int*)(lbl_801EB668 + 0x28e4) != 1) {
        return uVar1;
    }
    return 1;
}

s32 fn_80018694(int arg0);

s32 fn_800182B4(void) {
    int iVar1;
    int iVar2;
    s32 uVar3;
    u32* piVar4;

    piVar4 = &lbl_801EB660;
    uVar3 = -1;
    iVar2 = 1;
    do {
        if ((fn_80018694(iVar2) != 0) && (*piVar4 != 0)) {
            switch (*(int*)(*piVar4 + 0x28e4)) {
            case 1:
                return 0;
            case 2:
                uVar3 = 1;
                break;
            }
        }
        iVar2 += 1;
        piVar4 += 1;
    } while (iVar2 < 4);
    return uVar3;
}

void fn_8001834C(void) {
    lbl_801EB638 = 0;
    return;
}


s32 fn_8001835C(s32* arg0) {
    s32* piVar2;
    int iVar3;
    s32* piVar4;
    u8* pbVar5;
    u32 uVar6;
    u8 local_23[7];

    uVar6 = 1000;
    if (arg0 != (s32*)0x0) {
        *arg0 = 0;
    }
    piVar2 = &lbl_801EB65C;
    pbVar5 = local_23;
    piVar4 = &lbl_801EB640;
    iVar3 = 1;
    do {
        piVar2 = piVar2 + 1;
        *pbVar5 = 0;
        if ((((*piVar2 != 0) && (fn_80018694(iVar3) != 0)) && (*piVar4 != 0)) &&
            (*(int*)(*piVar2 + 0x28e4) != 0)) {
            if (GBAGetProcessStatus(iVar3, pbVar5) == 0) {
                if (arg0 != (s32*)0x0) {
                    arg0 = arg0 + 1;
                }
            }
            else {
                if (*(int*)(*piVar2 + 0x28e4) == 2) {
                    *pbVar5 = 100;
                }
                if ((99 < *pbVar5) && (*pbVar5 = 100, arg0 != (s32*)0x0)) {
                    arg0 += 1;
                }
                if (*pbVar5 < uVar6) {
                    uVar6 = (u32)*pbVar5;
                }
            }
        }
        iVar3 += 1;
        pbVar5 += 1;
        piVar4 += 1;
    } while (iVar3 < 4);
    if (uVar6 != 1000) {
        return uVar6 & 0xff;
    }
    return 0;
}

void fn_8001848C(void) {
    s32 auStack_8;

    fn_8001835C(&auStack_8);
    return;
}

//new file?

s32 lbl_801EB630;
s32 lbl_801EB634;

s32 fn_800184B0(void) {
    return lbl_801EB630;
}

void fn_800184C0(s32 arg0) {
    lbl_801EB630 = arg0;
    return;
}

void fn_800184CC(void) {
    lbl_801EB634 = OSGetTick();
    return;
}


void fn_800184F4(void) {
    u8 bVar1;
    u8 bVar2;
    u32 uVar3; //remove?
    u32 uVar4;
    int iVar5;
    s32 uVar6; //remove?
    s32 auStack_18[3];

    uVar6 = 0;
    uVar3 = fn_8001835C(auStack_18) & 0xff;
    if (lbl_801EB638 == uVar3) {
        if (uVar3 < 100) {
            bVar1 = 0;
            if ((lbl_801EB660 != 0) && (*(int*)(lbl_801EB660 + 0x28e4) == 1)) {
                bVar1 = 1;
            }
            uVar4 = (u32)bVar1;
            bVar2 = 0;
            if ((lbl_801EB664 != 0) && (*(int*)(lbl_801EB664 + 0x28e4) == 1)) {
                bVar2 = 1;
            }
            if (bVar2) {
                uVar4 += 1;
            }
            bVar2 = 0;
            if ((lbl_801EB668 != 0) && (*(int*)(lbl_801EB668 + 0x28e4) == 1)) {
                bVar2 = 1;
            }
            if (bVar2) {
                uVar4 += 1;
            }
            iVar5 = 1000;
            if (uVar3 == 0) {
                iVar5 = 7000;
            }
            uVar4 *= iVar5;
            if (SIProbe(0) == 0x40000) {
                uVar4 = uVar4 + 2000;
            }
            if (uVar4 < (u32)(OSGetTick() - lbl_801EB634) / 0x9e34) {
                uVar6 = 1;
            }
        }
    }
    else {
        lbl_801EB634 = OSGetTick();
    }
    lbl_801EB630 = uVar6;
    return;
}

u16 fn_80018644(void) {
    if (lbl_801EB65C == 0) {
        return 0;
    }
    return *(u16*)(lbl_801EB65C + 2);
}

//new file?
extern s32 lbl_800BE3D0;

s32 lbl_801F9AD0;
s32 lbl_801F9AD4;
s32 lbl_801F9AD8;
s32 lbl_801F9ADC;


void fn_8001866C(int arg0) {
    *(s32*)(&lbl_801F9AD0 + arg0 * 4) = *(s32*)(&lbl_800BE3D0 + arg0 * 4);
    return;
}

s32 fn_80018694(int arg0) {
    if (*(s32*)(&lbl_801F9AD0 + arg0) != 0) {
        return 0;
    }
    return 1;
}

u8 fn_800186C0(void) {
    u8 total = 0;
    if (lbl_801F9AD4 == 0) {
        ++total;
    }
    if (lbl_801F9AD8 == 0) {
        ++total;
    }
    if (lbl_801F9ADC == 0) {
        ++total;
    }
    return total;
}

//where does this go

u8 fn_80018724(u32* arg0, u32 arg1, u32 arg2) {
    u32 iVar1;

    memset(arg0, 0, 0x14);
    *arg0 = arg1;
    iVar1 = *arg0;
    if (iVar1 != 0) {
        arg0[1] = arg2;
        memset(*arg0, 0, arg2);
        arg0[4] = 1;
    }
    return iVar1 == 0;
}

//new file?

int fn_800187A8(s32* arg0) {
    if (arg0[2] >= arg0[3]) {
        return arg0[2] - arg0[3];
    }
    return arg0[2] + (arg0[1] - arg0[3]);
}

int fn_800187D0(s32* arg0) {
    if (arg0[2] > arg0[3]) {
        return (arg0[2] - arg0[3]) - 1;
    }
    return ((arg0[1] + arg0[2]) - arg0[3]) - 1;
}

//oh boy...

s32 fn_80018800(s32* arg0, u8* arg1, u32 arg2) {
    u8* puVar1;
    u8 uVar2;
    int iVar3;
    int iVar4;
    u8* puVar5;
    u8* puVar6;
    u32 uVar7;
    u32 uVar8;
    u32 uVar9;

    if (arg2 == 0) {
        return 0;
    }
    iVar4 = arg0[3];
    if (arg0[2] < iVar4) {
        iVar3 = arg0[1] - iVar4;
    }
    else {
        iVar3 = -iVar4;
    }
    if (arg0[2] + iVar3 < (int)arg2) {
        return 2;
    }
    if (arg0[1] < (int)(iVar4 + arg2)) {
        uVar8 = arg0[1] - iVar4;
        if ((arg1 != (u8*)0x0) && (puVar5 = (u8*)(*arg0 + iVar4), uVar8 != 0)) {
            uVar9 = uVar8 >> 3;
            puVar6 = arg1;
            uVar7 = uVar8;
            if (uVar9 != 0) {
                do {
                    *puVar6 = *puVar5;
                    puVar6[1] = puVar5[1];
                    puVar6[2] = puVar5[2];
                    puVar6[3] = puVar5[3];
                    puVar6[4] = puVar5[4];
                    puVar6[5] = puVar5[5];
                    puVar6[6] = puVar5[6];
                    puVar1 = puVar5 + 7;
                    puVar5 = puVar5 + 8;
                    puVar6[7] = *puVar1;
                    puVar6 = puVar6 + 8;
                    uVar9 = uVar9 - 1;
                } while (uVar9 != 0);
                uVar7 = uVar8 & 7;
                if (uVar7 == 0) goto LAB_800188ec;
            }
            do {
                uVar2 = *puVar5;
                puVar5 = puVar5 + 1;
                *puVar6 = uVar2;
                uVar7 = uVar7 - 1;
                puVar6 = puVar6 + 1;
            } while (uVar7 != 0);
        }
    LAB_800188ec:
        arg2 = arg2 - uVar8;
        if (arg1 != (u8*)0x0) {
            arg1 = arg1 + uVar8;
        }
        arg0[3] = 0;
    }
    if ((arg1 != (u8*)0x0) && (puVar5 = (u8*)(*arg0 + arg0[3]), arg2 != 0)
        ) {
        uVar8 = arg2 >> 3;
        uVar9 = arg2;
        if (uVar8 != 0) {
            do {
                *arg1 = *puVar5;
                arg1[1] = puVar5[1];
                arg1[2] = puVar5[2];
                arg1[3] = puVar5[3];
                arg1[4] = puVar5[4];
                arg1[5] = puVar5[5];
                arg1[6] = puVar5[6];
                puVar6 = puVar5 + 7;
                puVar5 = puVar5 + 8;
                arg1[7] = *puVar6;
                arg1 = arg1 + 8;
                uVar8 = uVar8 - 1;
            } while (uVar8 != 0);
            uVar9 = arg2 & 7;
            if (uVar9 == 0) goto LAB_8001899c;
        }
        do {
            uVar2 = *puVar5;
            puVar5 = puVar5 + 1;
            *arg1 = uVar2;
            arg1 = arg1 + 1;
            uVar9 = uVar9 - 1;
        } while (uVar9 != 0);
    }
LAB_8001899c:
    arg0[3] = arg0[3] + arg2;
    return 0;
}


s32 fn_800189B0(int* arg0, s8* arg1, u32 arg2) {
    s8* puVar1;
    u8 uVar2;
    int iVar3;
    u32 uVar4;
    int iVar5;
    s8* puVar6;
    s8* puVar7;
    u32 uVar8;
    u32 uVar9;

    if (arg2 == 0) {
        return 0;
    }
    iVar5 = arg0[3];
    if (arg0[2] < iVar5) {
        iVar3 = arg0[1] - iVar5;
    }
    else {
        iVar3 = -iVar5;
    }
    if (arg0[2] + iVar3 < (int)arg2) {
        return 2;
    }
    if ((int)(iVar5 + arg2) <= arg0[1]) goto LAB_80018aa0;
    uVar8 = arg0[1] - iVar5;
    puVar6 = (s8*)(*arg0 + iVar5);
    if (uVar8 != 0) {
        uVar9 = uVar8 >> 3;
        puVar7 = arg1;
        uVar4 = uVar8;
        if (uVar9 != 0) {
            do {
                *puVar7 = *puVar6;
                puVar7[1] = puVar6[1];
                puVar7[2] = puVar6[2];
                puVar7[3] = puVar6[3];
                puVar7[4] = puVar6[4];
                puVar7[5] = puVar6[5];
                puVar7[6] = puVar6[6];
                puVar1 = puVar6 + 7;
                puVar6 = puVar6 + 8;
                puVar7[7] = *puVar1;
                puVar7 = puVar7 + 8;
                uVar9 = uVar9 - 1;
            } while (uVar9 != 0);
            uVar4 = uVar8 & 7;
            if (uVar4 == 0) goto LAB_80018a94;
        }
        do {
            uVar2 = *puVar6;
            puVar6 += 1;
            *puVar7 = uVar2;
            uVar4 -= 1;
            puVar7 += 1;
        } while (uVar4 != 0);
    }
LAB_80018a94:
    arg2 -= uVar8;
    arg1 += uVar8;
    iVar5 = 0;
LAB_80018aa0:
    puVar6 = (s8*)(*arg0 + iVar5);
    if (arg2 != 0) {
        uVar8 = arg2 >> 3;
        if (uVar8 != 0) {
            do {
                *arg1 = *puVar6;
                arg1[1] = puVar6[1];
                arg1[2] = puVar6[2];
                arg1[3] = puVar6[3];
                arg1[4] = puVar6[4];
                arg1[5] = puVar6[5];
                arg1[6] = puVar6[6];
                puVar7 = puVar6 + 7;
                puVar6 += 8;
                arg1[7] = *puVar7;
                arg1 += 8;
                uVar8 = uVar8 - 1;
            } while (uVar8 != 0);
            arg2 &= 7;
            if (arg2 == 0) {
                return 0;
            }
        }
        do {
            uVar2 = *puVar6;
            puVar6 += 1;
            *arg1 = uVar2;
            arg1 += 1;
            arg2 -= 1;
        } while (arg2 != 0);
    }
    return 0;
}

s32 fn_80018B30(s32* arg0, s8* arg1, u32 arg2) {
    s8* puVar1;
    u8 uVar2;
    int iVar3;
    u32 uVar4;
    s8* puVar5;
    int iVar6;
    u8* puVar7;
    u32 uVar8;
    u32 uVar9;

    if (arg2 == 0) {
        return 0;
    }
    iVar6 = arg0[2];
    iVar3 = arg0[3];
    if (iVar6 < iVar3) {
        iVar3 -= iVar6;
    }
    else {
        iVar3 = (arg0[1] + iVar3) - iVar6;
    }
    if (iVar3 + -1 < (int)arg2) {
        return 2;
    }
    if (arg0[1] < (int)(iVar6 + arg2)) {
        uVar8 = arg0[1] - iVar6;
        puVar7 = (u8*)(*arg0 + iVar6);
        if (uVar8 != 0) {
            uVar9 = uVar8 >> 3;
            puVar5 = arg1;
            uVar4 = uVar8;
            if (uVar9 != 0) {
                do {
                    *puVar7 = *puVar5;
                    puVar7[1] = puVar5[1];
                    puVar7[2] = puVar5[2];
                    puVar7[3] = puVar5[3];
                    puVar7[4] = puVar5[4];
                    puVar7[5] = puVar5[5];
                    puVar7[6] = puVar5[6];
                    puVar1 = puVar5 + 7;
                    puVar5 = puVar5 + 8;
                    puVar7[7] = *puVar1;
                    puVar7 = puVar7 + 8;
                    uVar9 = uVar9 - 1;
                } while (uVar9 != 0);
                uVar4 = uVar8 & 7;
                if (uVar4 == 0) goto LAB_80018c1c;
            }
            do {
                *puVar7 = *puVar5;
                puVar7 += 1;
                uVar4 -= 1;
                puVar5 += 1;
            } while (uVar4 != 0);
        }
    LAB_80018c1c:
        arg0[2] = 0;
        arg2 -= uVar8;
        arg1 += uVar8;
    }
    puVar7 = (u8*)(*arg0 + arg0[2]);
    if (arg2 != 0) {
        uVar8 = arg2 >> 3;
        uVar9 = arg2;
        if (uVar8 != 0) {
            do {
                *puVar7 = *arg1;
                puVar7[1] = arg1[1];
                puVar7[2] = arg1[2];
                puVar7[3] = arg1[3];
                puVar7[4] = arg1[4];
                puVar7[5] = arg1[5];
                puVar7[6] = arg1[6];
                puVar5 = arg1 + 7;
                arg1 += 8;
                puVar7[7] = *puVar5;
                puVar7 += 8;
                uVar8 -= 1;
            } while (uVar8 != 0);
            uVar9 = arg2 & 7;
            if (uVar9 == 0) goto LAB_80018cbc;
        }
        do {
            uVar2 = *arg1;
            arg1 += 1;
            *puVar7 = uVar2;
            puVar7 += 1;
            uVar9 -= 1;
        } while (uVar9 != 0);
    }
LAB_80018cbc:
    arg0[2] = arg0[2] + arg2;
    return 0;
}

// FILE 11 - lbl_8006B2E0 bss

s32 lbl_801F9AE0;

void CreateResetThread(void) {
    memset(&lbl_801F9AE0, 0, 0x100);
    return;
}

void GCHandover_write(s32 arg0, u8 arg1) {
    (&lbl_801F9AE0)[arg0] = arg1;
    return;
}

u8 GCHandover_read(s32 arg0) {
    return (&lbl_801F9AE0)[arg0];
}

// FILE 12 - lbl_8006B2E8 bss

extern s32 lbl_8006B2E8;

s32 fn_80018D28(int arg0) {
    s32 uVar1 = 0;

    if (arg0 < 0xf) {
        uVar1 = *(s32*)(&lbl_8006B2E8 + arg0);
    }
    return uVar1;
}

int fn_80018D50(s32 arg0) {
    s32 uVar1;
    s32* puVar4;
    int iVar5;
    int iVar6;

    puVar4 = (s32*)&lbl_8006B2E8;
    iVar5 = 1;
    do {
        puVar4 += 1;
        uVar1 = 0;
        if (iVar5 < 0xf) {
            uVar1 = *puVar4;
        }
        iVar6 = iVar5;
    } while ((fn_8003A8F4(arg0, uVar1, strlen(uVar1)) != 0) && (iVar6 = 0, ++iVar5 < 0xf));
    return iVar6;
}

//EOF?

void fn_80018DDC(int arg0) {
    memset(arg0, 0, 4);
    *(s32*)(arg0 + 0x30) = 0;
    *(s32*)(arg0 + 0x34) = 0;
    *(s32*)(arg0 + 0x38) = 0;
    return;
}

s32 fn_80018E20(int arg0, s32* arg1) {
    int iVar1;
    int iVar2;
    s32 uVar3;
    int* piVar4;
    int iVar5;

    uVar3 = 0;
    while (1) {
        piVar4 = (int*)(arg0 + *(int*)(arg0 + 0x34) * 0xc);
        iVar2 = *piVar4;
        if (iVar2 == 0) {
            if (*(int*)(arg0 + 0x30) == 0) {
                return uVar3;
            }
            iVar5 = piVar4[1];
        }
        else {
            iVar5 = piVar4[1];
        }
        iVar1 = fn_800187D0(arg1);
        if (iVar1 < iVar2) {
            iVar2 = iVar1;
        }
        if (iVar2 == 0) break;
        fn_80018B30(arg1, (s8*)iVar5, iVar2);
        piVar4[1] = piVar4[1] + iVar2;
        piVar4[0] = piVar4[0] - iVar2;
        if (*piVar4 == 0) {
            *(int*)(arg0 + 0x34) += 1;
            if (3 < *(int*)(arg0 + 0x34)) {
                *(s32*)(arg0 + 0x34) = 0;
            }
            *(int*)(arg0 + 0x30) -= 1;
        }
        uVar3 = 1;
    }
    return uVar3;
}


u8 fn_80018F20(int arg0, s32* arg1, s32 arg2, s32 arg3) {
    s32* puVar1;
    u8 uVar2 = 0;

    if (*(int*)(arg0 + 0x30) < 4) {
        puVar1 = (s32*)(arg0 + *(int*)(arg0 + 0x38) * 0xc);
        puVar1[0] = arg2;
        puVar1[1] = arg3;
        *(int*)(arg0 + 0x38) += 1;
        if (*(int*)(arg0 + 0x38) >= 4) {
            *(s32*)(arg0 + 0x38) = 0;
        }
        uVar2 = 1;
        *(int*)(arg0 + 0x30) += 1;
    }
    fn_80018E20(arg0, arg1);
    return uVar2;
}

u8 fn_80018FAC(int arg0, s32* arg1, u32 arg2) {
    s32* puVar1;
    u8 uVar2;

    uVar2 = 0;
    if (*(int*)(arg0 + 0x30) < 4) {
        puVar1 = (s32*)(arg0 + *(int*)(arg0 + 0x38) * 0xc);
        puVar1[0] = 4;
        puVar1[1] = 2; //puVar1 + 2; //temp, fix types later
        puVar1[2] = arg2 << 0x18 | (arg2 & 0xff00) << 8 | arg2 >> 0x18 | arg2 >> 8 & 0xff00;
        *(int*)(arg0 + 0x38) += 1;
        if (3 < *(int*)(arg0 + 0x38)) {
            *(s32*)(arg0 + 0x38) = 0;
        }
        uVar2 = 1;
        *(int*)(arg0 + 0x30) += 1;
    }
    fn_80018E20(arg0, arg1);
    return uVar2;
}

void fn_80019058(int arg0, s32 arg1) {
    *(s32*)(arg0 + 0x30) = arg1;
    return;
}

void fn_80019060(s32* arg0) {
    arg0[0x0] = 0;
    arg0[0x1] = 0;
    arg0[0x2] = 0;
    memset(arg0 + 5, 0, 9);
    arg0[0x4] = 0;
    memset(arg0 + 3, 0, 4);
    arg0[0x8] = 1;
    arg0[0x9] = 0;
    arg0[0xa] = 0;
    arg0[0xb] = 0;
    arg0[0xc] = 0;
    return;
}


void fn_800190DC(s32* cmd, s32* arg1) {
    u8 bVar1;
    int iVar2;
    int iVar3;
    s32 uVar4;

    if (cmd[8] != 0) {
        switch (*cmd) {
        case 0x8: //STOP
            OSReport("tsuji MODE POTS, \n");
            cmd[8] = 0;
            break;
        case 0x9: //CONT
            OSReport("tsuji MODE TNOC, \n");
            cmd[8] = 0;
            break;
        case 0xa: //LOAD
            OSReport("tsuji MODE DAOL, \n");
            cmd[8] = 0;
            break;
        case 0xb: //CALL
            OSReport("tsuji MODE LLAC, \n");
            cmd[8] = 0;
            break;
        case 0xc: //WHO
            OSReport("tsuji MODE OHW, \n");
            OSReport("tsuji pGCCommand->m_ofsetBufCommand = %d, \n", cmd[4]);
            iVar2 = cmd[4];
            bVar1 = 0;
            iVar3 = fn_800187A8(arg1);
            if (iVar3 != 0) {
                if (9 - cmd[4] < iVar3) {
                    iVar3 = 9 - cmd[4];
                }
                iVar2 = 0;//fn_80018800(arg1, (u8*)0/*(s32*)(cmd + iVar2 + 0x14) */ , iVar3);
                if (iVar2 == 0) {
                    cmd[4] = cmd[4] + iVar3;
                    if (9 < (int)cmd[4]) {
                        do {
                            /* WARNING: Do nothing block with infinite loop */
                        } while (1);
                    }
                    if (cmd[4] == 9) {
                        cmd[4] = 0;
                        bVar1 = 1;
                    }
                }
            }
            if (bVar1) {
                cmd[8] = 0;
            }
            break;
        case 0xd: //PAUSe
            OSReport("tsuji MODE SUAP, \n");
            cmd[8] = 0;
            break;
        case 0xe: //CHaNGe
            OSReport("tsuji MODE GNHC, \n");
            cmd[8] = 0;
            break;
        default:
            if (*(u8*)(cmd + 3) != '\0') {
                OSReport("tsuji pGCCommand->m_BufCommand = % s, = 0x % 08x, \n", cmd + 3, cmd[3]);
            }
            iVar2 = cmd[4];
            bVar1 = 0;
            iVar3 = fn_800187A8(arg1);
            if (iVar3 != 0) {
                if (4 - cmd[4] < iVar3) {
                    iVar3 = 4 - cmd[4];
                }
                iVar2 = 0;//fn_80018800(arg1, (int)cmd + iVar2 + 0xc, iVar3);
                if (iVar2 == 0) {
                    cmd[4] = cmd[4] + iVar3;
                    if (4 < (int)cmd[4]) {
                        do {
                            /* WARNING: Do nothing block with infinite loop */
                        } while (1);
                    }
                    if (cmd[4] == 4) {
                        cmd[4] = 0;
                        bVar1 = 1;
                    }
                }
            }
            if (bVar1) {
                uVar4 = fn_80018D50(cmd[3]);
                *cmd = uVar4;
                *(u8*)(cmd + 3) = 0;
            }
        }
    }
    return;
}

s32 fn_80019330(s32* arg0, s32 arg1, s32 arg2, s32 arg3)

{
    int iVar1;
    s32 uVar2;
    s32 uVar3;

    uVar3 = 0;
    switch (arg0[9]) {
    case 0x0:
        arg0[9] = 1;
    case 0x1:
        uVar2 = fn_80018D28(5); //umm do we really need this...
        //fn_80018F20(arg1, arg2, 4, uVar2);
        arg0[9] = 2;
        break;
    case 0x2:
        if (arg0[8] == 0) {
            if (*(u8*)(arg0 + 5) == 0) {
                arg0[9] = 5;
            }
            else {
                if (strcmp(arg0 + 5, arg3) == 0) {
                    arg0[9] = 7;
                }
                else {
                    arg0[9] = 3;
                }
            }
            arg0[8] = 1;
            arg0[0] = 0;
        }
        break;
    case 0x3:
        //fn_80018F20(arg1, arg2, 4, fn_80018D28(1));
        arg0[9] = 4;
        break;
    case 0x4:
        if (arg0[8] == 0) {
            arg0[9] = 5;
            arg0[8] = 1;
            arg0[0] = 0;
        }
        break;
    case 0x5:
        //fn_80018F20(arg1, arg2, 4, fn_80018D28(3));
        //fn_80018FAC(arg1, arg2, 0x2004000);
        //fn_80018FAC(arg1, arg2, arg0[0xb]);
        //fn_80018F20(arg1, arg2, arg0[0xb], arg0[10]);
        arg0[9] = 6;
        break;
    case 0x6:
        if (arg0[8] == 0) {
            arg0[9] = 7;
            arg0[8] = 1;
            arg0[0] = 0;
        }
        break;
    case 0x7:
        //fn_80018F20(arg1, arg2, 4, fn_80018D28(4));
        //fn_80018FAC(arg1, arg2, 0x2004000);
        //fn_80018F20(arg1, arg2, 9, arg3);
        arg0[9] = 8;
        break;
    case 0x8:
        if (arg0[8] == 0) {
            arg0[9] = 0xb;
            arg0[8] = 1;
            arg0[0] = 0;
        }
        break;
    case 0x9:
        //fn_80018F20(arg1, arg2, 4, fn_80018D28(7));
        //fn_80018FAC(arg1, arg2, 0x2004000);
        arg0[9] = 10;
        break;
    case 0xa:
        if (arg0[8] == 0) {
            arg0[9] = 0;
            arg0[8] = 1;
            arg0[0] = 0;
        }
        break;
    case 0xb:
        uVar3 = 1;
    }
    return uVar3;
}











