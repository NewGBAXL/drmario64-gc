#include <types.h>

s32 lbl_801F9BE0;

void GCGBA_flagonUnsidentStatus(u32 arg0) {
	lbl_801F9BE0 = lbl_801F9BE0 | arg0;
	return;
}

void GCGBA_flagoffUnsidentStatus(u32 arg0) {
	lbl_801F9BE0 = lbl_801F9BE0 & ~arg0;
	return;
}
