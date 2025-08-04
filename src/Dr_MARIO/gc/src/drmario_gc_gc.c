#include "drmario_gc_gc.h"
#include "libultra.h"

//todo: fix
int lbl_2_bss_20;
int lbl_2_rodata_10E424;
int lbl_2_rodata_10F2F4;
int lbl_2_rodata_1035B0;

s32 soundSubInit(int arg0, int arg1) {
    int local_20[2];

    fn_80019C68();
    do {
        lbl_2_bss_20 = fn_2_5C1F4("Bwwdr_test.samp" + 3, 0, 0, 0, local_20);
        if (local_20[0] == 0x28) {
            gc_WaitForReset();
        }
    } while (local_20[0] == 0x28);
    fn_2_3CC();
    fn_80019C78();
    sndPushGroup(&lbl_2_rodata_10E424, 1, lbl_2_bss_20, &lbl_2_rodata_10F2F4, &lbl_2_rodata_1035B0);
    sndPushGroup(&lbl_2_rodata_10E424, 0, lbl_2_bss_20, &lbl_2_rodata_10F2F4, &lbl_2_rodata_1035B0);
    
    //todo
    /**(undefined*)(arg0 + 0x1c4) = 0;
    *(undefined4*)(arg0 + 0x1d0) = DAT_804ba4b0;
    *(undefined4*)(arg0 + 0x1d8) = DAT_804ba4b4;
    *(undefined4*)(arg0 + 0x1d4) = DAT_804ba4b8;
    *(undefined4*)(arg0 + 0x1c8) = DAT_804ba4b8;
    *(undefined4*)(arg0 + 0x1dc) = DAT_804ba4b4;
    *(undefined4*)(arg0 + 0x1cc) = DAT_804ba4bc;
    *(undefined4*)(arg1 + 0x90) = 0xd;
    *(undefined4*)(arg1 + 0x94) = 2;
    *(undefined4*)(arg1 + 0x98) = 500;*/
    
    if (lbl_2_bss_20 != 0) {
        DoFree();
    }
    return 1;
}

void soundSubQuit(void) {
    sndPopGroup();
    sndPopGroup();
    return;
}
