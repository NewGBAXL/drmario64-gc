#include "drmario_gc_unk.h"

#include "libultra.h"

s32* fn_2_3B4(s32 arg0, s32 arg1) {
	return (&lbl_2_data_10)[arg1];
}

void fn_2_3CC(int arg0) {
    switch (arg0) {
    case 0x27:
        fn_80019960();
        gc_resetSystem();
		break;
    case 0x29:
        fn_80019960();
        fn_2_5F3F8(0);
    }
    return;
}

s32 fn_2_424(void) {
    fn_80019C68();
    fn_2_5B9D4();
    fn_2_5BC74(0x6e, 0, 2);
    fn_2_5BDCC();
    fn_2_61110(0x40, 0x3e, 0x47);
    fn_80019C78();
    lbl_2_bss_333C = 0;
    return 0;
}

s32 fn_2_480(void) {
    if (OSIsThreadTerminated(&lbl_2_bss_3020) == 0) {
        return 0x24;
    }
    else {
        return lbl_2_bss_3338;
    }
}

void fn_2_4C4(void) {
    fn_80019C68();
    fn_2_5B9D4();
    fn_2_5BC74(0x6e, 0, 2);
    fn_2_5BDCC();
    fn_2_61110(0x40, 0x3e, 0x47);
    fn_80019C78();
    lbl_2_bss_333C = 0;
    lbl_2_bss_3338 = 0;
    return;
}

s32 fn_2_528(void) {
    int iVar1;
    s32 uVar2;

    lbl_2_bss_20 = 0x24;
    iVar1 = OSCreateThread(&lbl_2_bss_20, fn_2_4C4, 0, &lbl_2_bss_20, 0x3000, 0x12, 1);
    if (iVar1 == 0) {
        uVar2 = 0x23;
    }
    else {
        OSResumeThread(&lbl_2_bss_20);
        uVar2 = 0x21;
    }
    return uVar2;
}

void fn_2_59C(void) {
    if (lbl_2_bss_333C != 0) {
        DoFree();
    }
    return;
}
