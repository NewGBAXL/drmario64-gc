#include "PR/ultratypes.h"

void tiLoadTexData(s32* arg0, s32 arg1, s32 arg2) {
    s32* piVar1;
    s32* piVar2;
    s32 iVar3;
    s32 iVar4;

    piVar1 = (s32*)(*arg0 + 0xfU & 0xfffffff0);
    iVar4 = ExpandGZip(arg1, piVar1, arg2 - arg1);
    *arg0 = iVar4;
    piVar2 = (s32*)(*piVar1 + (s32)piVar1);
    *piVar1 = (s32)piVar2;
    iVar4 = piVar1[1];
    piVar1[1] = iVar4 + (s32)piVar1;
    iVar4 = *(s32*)(iVar4 + (s32)piVar1);
    if (0 < iVar4) {
        do {
            if ((u32)*piVar2 != 0) {
                *piVar2 += (s32)piVar1;
                iVar3 = *(s32*)*piVar2;
                if ((u32)iVar3 != 0) {
                    *(s32*)*piVar2 = iVar3 + (s32)piVar1;
                }
                iVar3 = *(s32*)(*piVar2 + 4);
                if ((u32)iVar3 != 0) {
                    *(s32*)(*piVar2 + 4) = iVar3 + (s32)piVar1;
                }
            }
            if ((u32)piVar2[1] != 0) {
                piVar2[1] += (s32)piVar1;
            }
            piVar2 += 2;
            //iVar4 -= 1;
        } while (iVar4 != 0);
    }
    return;
}

//void drawCursorPattern(s32* arg0, s32 /*undefined4*/ arg1, s32 /*undefined4*/ arg2, s32 arg3, s32 arg4,
//    s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
//}

/**
 * Original name: tiStretchAlphaTexItem
 */
//this will need a full redo
void drawCursorPattern(s32/*Gfx***/ gfxP, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
    s32 arg8) {
    //Gfx* gfx = *gfxP;
    s32 sp8[4];
    s32 sp18[4];
    s32 sp28[4];
    s32 sp38[4];
    s32 sp48[4];
    s32 i;
    s32 temp;

    temp = arg7 + arg3;

    sp8[0] = (arg5 * 4) - (arg3 * 2);
    sp8[3] = sp8[0] + temp * 4;
    sp8[1] = sp8[0] + arg3 * 4;
    sp8[2] = sp8[3] - arg3 * 4;

    sp28[0] = 0;
    sp28[1] = (arg3 - 1) << 5;
    sp28[2] = arg3 << 5;

    temp = arg8 + arg4;

    sp18[0] = (arg6 * 4) - (arg4 * 2);
    sp18[3] = sp18[0] + temp * 4;
    sp18[1] = sp18[0] + arg4 * 4;
    sp18[2] = sp18[3] - arg4 * 4;

    sp38[0] = 0;
    sp38[1] = (arg4 - 1) << 5;
    sp38[2] = arg4 << 5;

    sp48[0] = -0x400;
    sp48[1] = 0;
    sp48[2] = 0x400;

    for (i = 0; i < 5/*ARRAY_COUNTU(_pnts_871)*/; i++) {
        // Cast away the const
        u8* temp_a3_2 = 0;/*(u8*)_pnts_871[i] */ ;

        gSPScisTextureRectangle(0/*gfx++*/, sp8[temp_a3_2[0]], sp18[temp_a3_2[1]], sp8[temp_a3_2[2]], sp18[temp_a3_2[3]],
            0/*G_TX_RENDERTILE*/, sp28[temp_a3_2[4]], sp38[temp_a3_2[5]], sp48[temp_a3_2[6]],
            sp48[temp_a3_2[7]]);
    }
    //*gfxP = gfx;
}
