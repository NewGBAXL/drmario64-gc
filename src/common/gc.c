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

void gc_soundQuit(void) {
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

void gc_songStop(s32 arg0) {
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

//..


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
