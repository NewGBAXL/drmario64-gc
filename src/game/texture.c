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

//extern GXRenderModeObj;
#include "dolphin/gx/GXStruct.h"


extern s32 lbl_8022DAF4;
extern s32 lbl_8022DAF8;
extern s32 lbl_8022DAFC;

extern s32 lbl_800F30C0;
extern s32 lbl_800F30C4;

extern s32 ___OSCurrHeap;

extern s32 lbl_801BCA10;
extern s32 lbl_801BCA14;

extern s32 lbl_8006A8BC;
extern s32 lbl_8006A8C0;
extern s32 lbl_8006A8D0;

extern s32 lbl_800BE100;

extern s32 lbl_8022FAF8;

void fn_8000BA98(GXRenderModeObj* rm, s32 maxHeaps) {
	int arenaStart;
	s32 arenaStart2;
	u32 arenaEnd;
	s16 uVar4;
	double dVar5;

	OSInit();
	DVDInit();
	VIInit();
	PADSetSpec(5);
	PADInit();
	arenaStart = OSGetArenaLo();
	OSGetArenaHi();
	lbl_8022DAFC = arenaStart + 0x1fU & 0xffffffe0;
	arenaStart = (*(u16*)(rm + 1) + 0xf & 0xfff0) * (u32) * (u16*)(rm + 2) * 2 + 0x1f;
	lbl_8022DAF4 = lbl_8022DAFC + arenaStart & 0xffffffe0;
	lbl_8022DAF8 = lbl_8022DAF4;
	OSSetArenaLo(lbl_8022DAF4 + arenaStart & 0xffffffe0);
	arenaStart2 = OSGetArenaLo();
	arenaEnd = OSGetArenaHi();
	arenaStart = OSInitAlloc(arenaStart2, arenaEnd, maxHeaps);
	OSSetArenaLo();
	lbl_800F30C0 = OSCreateHeap(arenaStart + 0x1fU & 0xffffffe0, arenaEnd & 0xffffffe0);
	lbl_800F30C4 = lbl_800F30C0;
	OSSetCurrentHeap();
	___OSCurrHeap = lbl_800F30C0;
	OSSetArenaLo(arenaEnd & 0xffffffe0);
	VIConfigure(rm);
	lbl_801BCA10 = OSAllocFromHeap(___OSCurrHeap, 0x40000);
	lbl_801BCA14 = GXInit(lbl_801BCA10, 0x40000);
	dVar5 = (double)lbl_8006A8BC;
	GXSetViewport(dVar5, dVar5,
		(double)(float)((double)CONCAT44(0x43300000, (u32) * (u16*)(rm + 1)) -
			lbl_8006A8D0),
		(double)(float)((double)CONCAT44(0x43300000, (u32) * (u16*)((int)rm + 6)) -
			lbl_8006A8D0), dVar5, (double)lbl_8006A8C0);
	GXSetScissor(0, 0, *(s16*)(rm + 1), *(s16*)((int)rm + 6));
	fn_80065620(*(s16*)((int)rm + 6), *(s16*)(rm + 2));
	uVar4 = GXSetDispCopyYScale();
	GXSetDispCopySrc(0, 0, *(s16*)(rm + 1), *(s16*)((int)rm + 6));
	GXSetDispCopyDst(*(s16*)(rm + 1), uVar4);
	fn_80065988(0, 0, 1, &lbl_800BE100);
	if (*(char*)((int)rm + 0x19) == '\0') {
		GXSetPixelFmt(0, 0);
	}
	else {
		GXSetPixelFmt(2, 0);
	}
	GXCopyDisp(lbl_8022DAF4, 1);
	GXSetDispCopyGamma(0);
	VISetNextFrameBuffer(lbl_8022DAFC);
	lbl_8022DAF4 = lbl_8022FAF8;
	VIFlush();
	VIWaitForRetrace();
	if ((rm /* & 1*/) != 0) {
		VIWaitForRetrace();
	}
	return;
}
