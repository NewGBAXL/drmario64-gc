#include "drmario_gc.h"
#include "libultra.h"

s32 main(void) {
    s32* puVar1;
    int iVar2;

    GCNIS_nuGfxInit_relocate();
    fn_2_5B98C();
    GCHandover_write(8, 1);
    fn_2_5F9F8();
    SetDVDError_DispFunction(0);
    mainStroy_Init();
    gc_memoryCard_sizeAdjust(0x1000);
    eeprom_bufferp = (s32)DoMalloc();
    Gzip_bufferp = (s32)DoMalloc(0x200000);
    Heap_bufferp = (s32)DoMalloc(0x200000);
    gc_getEFB_init();
    iVar2 = 0x40000;
    puVar1 = &Gzip_bufferp;
    do {
        *puVar1 = 0;
        puVar1[1] = 0;
        puVar1[2] = 0;
        puVar1[3] = 0;
        puVar1[4] = 0;
        puVar1[5] = 0;
        puVar1[6] = 0;
        puVar1[7] = 0;
        puVar1 = puVar1 + 8;
        iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    iVar2 = 0x80;
    puVar1 = &eeprom_bufferp;
    do {
        *puVar1 = 0;
        puVar1[1] = 0;
        puVar1[2] = 0;
        puVar1[3] = 0;
        puVar1[4] = 0;
        puVar1[5] = 0;
        puVar1[6] = 0;
        puVar1[7] = 0;
        puVar1[8] = 0;
        puVar1[9] = 0;
        puVar1[10] = 0;
        puVar1[0xb] = 0;
        puVar1[0xc] = 0;
        puVar1[0xd] = 0;
        puVar1[0xe] = 0;
        puVar1[0xf] = 0;
        puVar1[0x10] = 0;
        puVar1[0x11] = 0;
        puVar1[0x12] = 0;
        puVar1[0x13] = 0;
        puVar1[0x14] = 0;
        puVar1[0x15] = 0;
        puVar1[0x16] = 0;
        puVar1[0x17] = 0;
        puVar1[0x18] = 0;
        puVar1[0x19] = 0;
        puVar1[0x1a] = 0;
        puVar1[0x1b] = 0;
        puVar1[0x1c] = 0;
        puVar1[0x1d] = 0;
        puVar1[0x1e] = 0;
        puVar1[0x1f] = 0;
        puVar1 += 0x20;
        iVar2 -= 1;
    } while (iVar2 != 0);
    iVar2 = 0x40000;
    puVar1 = &Heap_bufferp;
    do {
        *puVar1 = 0;
        puVar1[1] = 0;
        puVar1[2] = 0;
        puVar1[3] = 0;
        puVar1[4] = 0;
        puVar1[5] = 0;
        puVar1[6] = 0;
        puVar1[7] = 0;
        puVar1 += 8;
        iVar2 -= 1;
    } while (iVar2 != 0);
    nuGfxFuncSet(mainproc);
    fn_2_59C();
    DoFree(Heap_bufferp);
    DoFree(Gzip_bufferp);
    DoFree(eeprom_bufferp);
    gc_soundQuit();
    gfxTaskStartFrameCopyFunc_set(0);
    gc_getEFB_exit();
    return 0;
}


void drMarioRetrace(bool arg0) {
    if (arg0 == 0) {
        lbl_2_bss_0 += 1;
        lbl_2_bss_0 += 1;
        if (*subproc_nuGfxFunc != 0x0) {
            (*subproc_nuGfxFunc)();
        }
    }
    return;
}


