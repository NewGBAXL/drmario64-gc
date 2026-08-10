#include <types.h>

s32 lbl_801F9BE0;

void GCGBA_800195D4(u32 arg0) {
	lbl_801F9BE0 = arg0;
	return;
}

s32 GCGBA_800195E0(void) {
	return lbl_801F9BE0;
}

void GCGBA_flagonUnsidentStatus(u32 arg0) {
	lbl_801F9BE0 = lbl_801F9BE0 | arg0;
	return;
}

void GCGBA_flagoffUnsidentStatus(u32 arg0) {
	lbl_801F9BE0 = lbl_801F9BE0 & ~arg0;
	return;
}
