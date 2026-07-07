#include <types.h>

s8 tightFlag;
s32 lbl_801BCA08;
s32 lbl_801BCA0C;

//type mismatch idk
s8 StretchTexBlock_SetTightFlag(u8 arg0) {
	tightFlag = arg0;
	return tightFlag;
}

s8 StretchTexBlock_ReadTightFlag(void) {
	return tightFlag;
}

void fn_8000BA60(s32 arg0) {
	lbl_801BCA08 = arg0;
	return;
}

s32 fn_8000BA6C(void) {
	return lbl_801BCA08;
}

void GlobalSubCycleType_SetFlag(s32 arg0) {
	lbl_801BCA0C = arg0;
	return;
}

s32 GlobalSubCycleType_ReadFlag(void) {
	return lbl_801BCA0C;
}
