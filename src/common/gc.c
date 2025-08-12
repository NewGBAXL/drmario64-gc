#include "libultra.h"
#include "gc.h"

void DoMalloc(s32 arg0) {
	if ((u32)OSAllocFromHeap(__OSCurrHeap, arg0) != 0) {
		alloc_counter += 1;
	}
}

void DoFree(s32 arg0) {
	if (arg0 != 0) {
		OSFreeToHeap(__OSCurrHeap, arg0);
		alloc_counter -= 1;
	}
}

//..
void fn_2_5B98C(void) {
	//DAT_809b4154 = 0xffffffff;
	//DAT_809b4158 = 0xffffffff;
	//DAT_809b415c = 0xffffffff;
	//DAT_809b4160 = 0xffffffff;
	sndSetMaxVoices(0x30, 0x10);
	return;
}

void gc_soundQuit(void) {
	s32 unused;

	sndSilence();
	sndSetAuxProcessingCallbacks(0, 0, 0, 0xff, 0, 0, 0, 0xff, 0);
	sndAuxCallbackShutdownChorus(&cho);
	sndAuxCallbackShutdownReverbHI(&revH);
	soundSubQuit();
	return;
}


s32 gc_songPlay(u32 arg0, s32 arg1) {
	u32 uVar1;
	s32 iVar2;
	s32 uVar3; //custom data

	//gc_songStop
	fn_2_5BBC8(arg1);

	if (fn_2_3B4(songTbl, arg0) == 0) {
		lastsong_id = 0xffffffff;
	}
	else {
		lastsong_id = sndSeqPlayEx(songTbl & 0xffff, arg0 & 0xffff, fn_2_3B4(songTbl, arg0), 0, 0);
	}
	return lastsong_id;
}

void _gc_song_stop(s32 arg0) {
	if (arg0 != 0xffff) {
		sndSeqStop();
	}
}

void gc_songStop(u32 arg0) {
	if ((&lbl_2_bss_212DB4)[arg0] != 0xffff) {
		sndSeqStop();
	}
	(&lbl_2_bss_212DB4)[arg0] = -1;
	return;
}


s32 _gc_songGetValid(s32 arg0) {
	if (arg0 != 0xffff) {
		return sndSeqGetValid();
	}
	else {
		return 0;
	}
}

void _gc_sePlay(u16 arg0, u32 arg1, u32 arg2) {
	sndFXStartEx(arg0, arg1, arg2, 0);
	return;
}

void fn_2_5BC74(u32 arg0, s32 arg1, u8 arg2)

{
	switch (arg2) {
		case '\0':
			sndVolume(arg0, arg1, 0xfd);
			break;
		case '\x01':
			sndVolume(arg0, arg1, 0xfe);
			break;
		default:
			sndVolume(arg0, arg1, 0xff);
			break;
	}
	return;
}

void _gc_songFadeSong(s32 arg0, u32 arg1, s32 arg2) {
	if (arg0 != 0xffff) {
		if ((arg1 & 0xff) == 0) {
			sndSeqVolume(0, arg2, arg0, 1);
		}
		else {
			sndSeqVolume(arg1, arg2, arg0, 0);
		}
	}
	return;
}

void gc_soundSetOutputMode(u32 arg0) {
	switch (arg0) {
	case 0:
		sndOutputMode(0);
		OSSetSoundMode(0);
		GCHandover_write(9, 1);
		return;
	case 1:
		sndOutputMode(1);
		OSSetSoundMode(1);
		GCHandover_write(9, 0);
		return;
	case 2:
		sndOutputMode(2);
		OSSetSoundMode(1);
		GCHandover_write(9, 2);
		return;
	}	
}


void fn_2_5BDCC(void) {
	if ((u32)OSGetSoundMode() == 1) {
		GCHandover_write(9, 0);
	}
	if ((u32)OSGetSoundMode() == 0) {
		GCHandover_write(9, 1);
	}
	switch (GCHandover_read(9)) {
	case 0:
		sndOutputMode(1);
		OSSetSoundMode(1);
		GCHandover_write(9, 0);
		break;
	case 1:
		sndOutputMode(0);
		OSSetSoundMode(0);
		GCHandover_write(9, 1);
		break;
	case 2:
		sndOutputMode(2);
		OSSetSoundMode(1);
		GCHandover_write(9, 2);
		break;
	}
}

void gc_soundAllStop(void) {
	sndSilence();
}

void gc_soundAllStop_check(void) {
	sndIsIdle();
}

void SetDVDError_DispFunction(s32* arg0) {
	if (arg0 == 0) {
		//lbl_2_bss_213054 = (u32*)&fn_80019D00;
	}
	else {
		lbl_2_bss_213054 = arg0;
	}
}

s32 /*fix type*/ fn_2_5BF08(s32 /*fix type*/ arg0) {
	lbl_2_data_25120 = arg0;
	lbl_2_bss_21437C = 1;
	return 0;
}

//..

extern fn_2_5BF24();

void fn_2_5C1F4(void) {
	fn_2_5BF24();
}

u32 gc_GetDVDDrive(void) {
	u32 uVar1;

	switch (DVDGetDriveStatus()) {
	case 0xffffffff:
		uVar1 = 0x18;
		break;
	case 4:
		uVar1 = 0x1b;
		break;
	case 5:
		uVar1 = 0x1c;
		break;
	case 6:
		uVar1 = 0x1d;
		break;
	case 0xb:
		uVar1 = 0x20;
		break;
	default:
		uVar1 = 0x0;
	}
	return uVar1;
}

void gc_OSGetTime(void) {
	OSGetTime();
}

void gc_getEFB_init(void) {
	if (EFB_bufferp != 0) {
		OSFreeToHeap(__OSCurrHeap);
		alloc_counter -= 1;
	}
	EFB_bufferp = (s16*)OSAllocFromHeap(__OSCurrHeap, 0x25800);
	if (EFB_bufferp != 0) {
		alloc_counter += 1;
	}
}

void gc_getEFB_exit(void) {
	if (EFB_bufferp != 0) {
		OSFreeToHeap(__OSCurrHeap);
		alloc_counter -= 1;
	}
	EFB_bufferp = 0;
}

s16* gc_getEFB_getBuffer(void) {
	return EFB_bufferp;
}


s16* gc_getEFB_RGBA16(void) {
	short* psVar1;
	u32 uVar2;
	u32 uVar3;
	u32* uStack_18;
	u16 local_17;
	u16 local_16;
	u16 local_15;

	uVar2 = 0;
	psVar1 = EFB_bufferp;
	do {
		uVar3 = 0;
		do {
			GXPeekARGB(uVar3 & 0xffff, uVar2 & 0xffff, &uStack_18);
			uVar3 = uVar3 + 2;
			local_17 = (u16)((s32)(u32)local_17 >> 3);
			local_16 = (u16)((s32)(u32)local_16 >> 3);
			local_15 = (u16)((s32)(u32)local_15 >> 3);
			*psVar1 = (u16)local_17 * 0x800 + (u16)local_16 * 0x40 + (u16)local_15 * 2 + 1;
			psVar1 += 1;
		} while ((int)uVar3 < 0x280);
		uVar2 = uVar2 + 2;
	} while ((int)uVar2 < 0x1e0);
	return EFB_bufferp;
}

//..


s32 gc_memoryCard_errorCheck(int code, char* name) {
	switch (code) { //byte casting?
	case 0:
		return 0;
	case -1:
		return 18;
	case -2:
		return 6;
	case -3:
		return 2;
	case -4:
		return 9;
	case -5:
		return 17;
	case -6:
		return 5;
	case -7:
		return 13;
	case -8:
		return 14;
	case -10:
		return 10;
	case -11:
		return 15;
	case -12:
		return 11;
	case -13:
		return 4;
	case -14:
		return 12;
	case -128:
		return 3;
	default:
		return 1;
	}
}

s32 fn_2_5CE3C(void) {
	lbl_2_bss_1FA728 = 1;
	return 0;
}

//..

/*not correct*/
u32 gc_memoryCard_sizeAdjust(u32 arg0) {
	s32 rounded = (s32)arg0 >> 13;

	if (arg0 != (u32)(rounded << 13)) {
		rounded + 1;
	}

	return (u32)(rounded << 13);
}

//..

void fn_2_5CFC8(s32 arg0) {
	lbl_2_bss = arg0;
	return;
}

void fn_2_5EFA0() {
	lbl_2_bss_2243FC = 0xffffffff;
	//lbl_2_bss_224400 = 0xffffffff;
	return;
}

//..

void fn_2_5F26C(s32 arg0, s32* arg1) {
	s32 uVar1;

	uVar1 = lbl_2_bss;
	fn_2_5EFB8(0, arg0);
	*arg1 = 2;
	lbl_2_bss = uVar1;
	return;
}

s32 fn_2_5F2C8(s32 arg0) {
	switch (arg0) {
	case 0:
	case 3:
	case 4:
	case 5:
	case 7:
	case 8:
	case 9:
	case 10:
	case 0xb:
	case 0xd:
	case 0xe:
	case 0xf:
	case 0x10:
	case 0x11:
		return 0;
	default:
		return 1;
	}
}

s32 fn_2_5F2F8(void) {
	int iVar1;
	s32 uVar2;
	s32 auStack_10[8];

	if ((lbl_2_data_25120 == 0) || (OSIsThreadTerminated(&DAT_809b1ae8) != 0)) {
		do {
			iVar1 = gc_memoryCard_errorCheck(CARDProbeEx(0, auStack_10, &DAT_8099bac4), "CARDProbeEx");
		} while (iVar1 == 0x12);
		lbl_2_data_25274 = iVar1;
		if ((iVar1 == 0) && (DAT_8099bac4 != 0x2000)) {
			lbl_2_data_25274 = 8;
		}
	}
	switch (lbl_2_data_25274) {
	case 0:
	case 3:
	case 4:
	case 5:
	case 7:
	case 8:
	case 9:
	case 10:
	case 0xb:
	case 0xd:
	case 0xe:
	case 0xf:
	case 0x10:
	case 0x11:
		uVar2 = 0;
		break;
	default:
		uVar2 = 1;
	}
	return uVar2;
}

void gc_resetSystem(void) {
	OSResetSystem(0, 0, 1);
	return;
}

void fn_2_5F3F8(s32 arg0) {
	OSResetSystem(1, 0, arg0);
	return;
}

void fn_2_5F424(void) {
	int iVar1;

	DVDCancelAll();
	OSCancelThread(&DAT_809b3e10);
	do {
		iVar1 = OSIsThreadTerminated(&DAT_809b3e10);
	} while (iVar1 == 0);
	DAT_807a1060 = 0xfffffed4;
	lbl_2_data_25120 = 0x25;
	return;
}

void fn_2_5F538(void) {
	DAT_809b1e08 = fn_2_5DF88(DAT_809b1e00, DAT_809b1e04);
	return;
}

void fn_2_5F654(void) {
	DAT_809b1e08 = gc_memoryCardLoad(DAT_809b1e00, DAT_809b1e04);
	return;
}

void fn_2_5F770(void) {
	s32 uVar1;
	int iVar2;
	s32 uVar3;
	int iVar4;

	uVar1 = DAT_809b1e00;
	DAT_8099bac8 = 0;
	iVar2 = fn_2_5CE50(DAT_809b1e00);
	if ((iVar2 == 0) || (iVar2 - 4U < 2)) {
		do {
			iVar2 = gc_memoryCard_errorCheck(CARDFormat(uVar1), "CARDFormat");
		} while (iVar2 == 0x12);
	}
	do {
		iVar4 = gc_memoryCard_errorCheck(CARDUnmount(uVar1), "CARDUnmount");
	} while (iVar4 == 0x12);
	if (iVar4 == 2) {
		iVar4 = 0;
	}
	if (iVar2 != 0) {
		iVar4 = iVar2;
	}
	DAT_809b1e08 = iVar4;
	return;
}

void fn_2_5F914(void) {
	lbl_2_bss_210A68 = fn_2_5EEA0(1);
	return;
}

//..

void fn_2_5F9F8(void) {
	if (DAT_809c57d4 == 0) {
		OSCreateAlarm(&DAT_809c57a8);
	}
	DAT_809c57d4 = 1;
	lbl_2_bss_212D8C = 0;
	return;
}

void fn_2_5FA54(void) {
	OSResumeThread(lbl_2_bss_224430);
	if (lbl_2_bss_212D8C != 0) {
		OSResumeThread();
	}
	return;
}

void fn_2_5FA98(void) {
	OSSetAlarm(&DAT_809c57a8, 0x140000, 0, 0x13c680, fn_2_5FA54);
	lbl_2_bss_224430 = OSGetCurrentThread();
	if (lbl_2_bss_212D8C != 0) {
		OSSuspendThread();
	}
	OSSuspendThread(lbl_2_bss_224430);
	return;
}

void fn_2_5FB68(void) {
	s32 local_c[2];

	//DAT_809b4134 = fn_2_5BF24(DAT_809b4130, DAT_809b4134, DAT_809b4140, DAT_809b4144, local_c, 1);
	//DAT_809b4138 = local_c[0];
	return;
}

void fn_2_5FCF0(void) {
	lbl_2_bss_212D88 = 0;
	fn_2_5BFC0();
	return;
}

void fn_2_5FD20(void) {
	VIWaitForRetrace();
	return;
}

void fn_2_5FD40(int arg0) {
	switch (arg0) {
	case 0:
		GCHandover_write(0xa, 1);
		break;
	case 1:
		GCHandover_write(0xb, 0);
		break;
	case 2:
		GCHandover_write(0xc, 2);
		break;
	}
	if (((GCHandover_read(0xa) == 1) && (GCHandover_read(0xb) == 1)) && (GCHandover_read(0xc) ==1)) {
		GCHandover_write(0xd, 1);
	}
	return;
}

s32 fn_2_610B4(void) {
	int iVar1;

	fn_2_60258(0, 0, 0, 0, 0);
	fn_2_5EFA0();
	//fn_2_5F26C(&lbl_2_bss_224638, &lbl_2_bss_224654);
	fn_2_5CFC8(iVar1 + -1);
	iVar1 = GCHandover_read(8);
	return 0;
}

void fn_2_61110(s32 arg0, s32 arg1, s32 arg2) {
	lbl_2_data_25358[0] = arg0;
	lbl_2_data_25358[1] = arg1;
	lbl_2_data_25358[2] = arg2;
	return;
}

