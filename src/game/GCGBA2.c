#include <types.h>

s32 lbl_801F9BE8[4]; //global
const char* lbl_8006B33C[4];

const char* lbl_8006B328[5] = { "NULL", "CONTROLL", "AGBMARIO", "AGBPON", "AGBCOOKIE" };

void GCGBA_80019618(u32 arg0, u32 arg1) {
	lbl_801F9BE8[arg0] = arg1;
	lbl_8006B33C[arg0] = lbl_8006B328[lbl_801F9BE8[arg0]];
	return;
}

void GCGBA_80019658(s32 arg0) {
	lbl_801F9BE8[1] = arg0;
	lbl_8006B33C[1] = lbl_8006B328[lbl_801F9BE8[1]];
	lbl_801F9BE8[2] = arg0;
	lbl_8006B33C[2] = lbl_8006B328[lbl_801F9BE8[2]];
	lbl_801F9BE8[3] = arg0;
	lbl_8006B33C[3] = lbl_8006B328[lbl_801F9BE8[3]];
	return;
}

void GCGBA_800196A8(s32 arg0) {
	lbl_801F9BE8[0] = arg0;
	lbl_8006B33C[0] = lbl_8006B328[lbl_801F9BE8[0]];
	lbl_801F9BE8[1] = arg0;
	lbl_8006B33C[1] = lbl_8006B328[lbl_801F9BE8[1]];
	lbl_801F9BE8[2] = arg0;
	lbl_8006B33C[2] = lbl_8006B328[lbl_801F9BE8[2]];
	lbl_801F9BE8[3] = arg0;
	lbl_8006B33C[3] = lbl_8006B328[lbl_801F9BE8[3]];
	return;
}
