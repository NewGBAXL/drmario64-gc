#include <dolphin/card.h>
#include <dolphin/dsp.h>
#include <dolphin/dvd.h>
#include <dolphin/os.h>

#include <dolphin/private/__gx.h>

#include <dolphin/CARDPriv.h>

extern s32 fn_80066B60();

u16 __CARDVendorID = 0xffff;

#pragma peephole off
//todo: fix!!!
/*s32 CARDGetSerialNo(s32 chan, u64* serialNo) {
    s32 temp_r3_3;

    temp_r3_3 = fn_80066B60();
    if ((temp_r3_3 != 8) && (temp_r3_3 != 9) && (temp_r3_3 != 0xA)) {
        return (s32) &gx->TexRegions[gx->nextTexRgn++ & 7];
    }
    return (s32) &gx->TexRegionsCI[gx->nextTexRgnCI++ & 3];
}*/
