#include "libultra.h"

s32 sintable;

/*void matrixMulL(u32* arg0, u32* arg1, s32* arg2) {
}*/

void makeTransrateMatrix(u32* arg0, u32 arg1, u32 arg2, u32 arg3) {
	*arg0 = 0x8000;
	arg0[1] = 0;
	arg0[2] = 0;
	arg0[3] = 0;
	arg0[4] = 0;
	arg0[5] = 0x8000;
	arg0[6] = 0;
	arg0[7] = 0;
	arg0[8] = 0;
	arg0[9] = 0;
	arg0[10] = 0x8000;
	arg0[0xb] = 0;
	arg0[0xc] = arg1;
	arg0[0xd] = arg2;
	arg0[0xe] = arg3;
	arg0[0xf] = 0x8000;
	return;
}

void makeScaleMatrix(u32* arg0, u32 arg1) {
	*arg0 = arg1;
	arg0[1] = 0;
	arg0[2] = 0;
	arg0[3] = 0;
	arg0[4] = 0;
	arg0[5] = arg1;
	arg0[6] = 0;
	arg0[7] = 0;
	arg0[8] = 0;
	arg0[9] = 0;
	arg0[10] = arg1;
	arg0[0xb] = 0;
	arg0[0xc] = 0;
	arg0[0xd] = 0;
	arg0[0xe] = 0;
	arg0[0xf] = 0x8000;
	return;
}

s32 quicky(s32 arg0) {
	s32 iVar1;
	arg0 = ((s32)(short)arg0 >> 6 & 0x3ffU) * 2;
	iVar1 = (s32)*(short*)(sintable + arg0);
	if ((arg0 & 0x3f) != 0) {
		iVar1 += ((s32)((arg0 & 0x3f) * (*(short*)(sintable + arg0 + 2) - iVar1)) >> 6);
	}
	return iVar1;
}

void makeMatrix(s32* arg0, u32 arg1, u32 arg2, u32 arg3, s32 arg4, s32 arg5, s32 arg6) {
	s32 iVar1;
	s32 iVar2;
	s32 iVar3;
	u32 uVar4;
	s32 iVar5;
	s32 iVar6;
	s32 iVar7;
	s32 iVar8;

	arg0[0xb] = 0;
	arg0[7] = 0;
	arg0[3] = 0;
	arg0[0xf] = 0x8000;
	arg0[0xc] = arg4;
	arg0[0xd] = arg5;
	arg0[0xe] = arg6;
	iVar1 = quicky(arg1);
	iVar2 = quicky(arg1);
	iVar3 = quicky(arg2);
	iVar6 = quicky(arg2);
	iVar5 = quicky(arg3);
	iVar8 = quicky(arg3);
	arg0[9] = -iVar1;
	arg0[1] = iVar2 * iVar5 >> 0xf;
	arg0[5] = iVar2 * iVar8 >> 0xf;
	arg0[8] = iVar2 * iVar3 >> 0xf;
	iVar7 = iVar1 * iVar3 >> 0xf;
	arg0[10] = iVar2 * iVar6 >> 0xf;
	*arg0 = iVar5 * iVar7 + iVar8 * iVar6 >> 0xf;
	arg0[4] = iVar8 * iVar7 - iVar5 * iVar6 >> 0xf;
	iVar1 = iVar1 * iVar6 >> 0xf;
	arg0[2] = iVar5 * iVar1 + iVar8 * iVar3 >> 0xf;
	arg0[6] = iVar8 * iVar1 - iVar5 * iVar3 >> 0xf;
	return;
}
