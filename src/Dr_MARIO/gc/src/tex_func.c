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
