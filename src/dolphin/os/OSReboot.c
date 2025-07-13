#include "dolphin/dvd.h"
#include "dolphin/os.h"
#include "dolphin/os/OSBootInfo.h"
#include "dolphin/os/OSContext.h"
#include "dolphin/os/OSInterrupt.h"
#include "dolphin/types.h"

typedef struct ApploaderHeader {
  // total size: 0x20
  char date[16];  // offset 0x0, size 0x10
  u32 entry;      // offset 0x10, size 0x4
  u32 size;       // offset 0x14, size 0x4
  u32 rebootSize; // offset 0x18, size 0x4
  u32 reserved2;  // offset 0x1C, size 0x4
} ApploaderHeader;

struct {
  // total size: 0x1C
  int valid;                 // offset 0x0, size 0x4
  unsigned long restartCode; // offset 0x4, size 0x4
  unsigned long bootDol;     // offset 0x8, size 0x4
  void* regionStart;         // offset 0xC, size 0x4
  void* regionEnd;           // offset 0x10, size 0x4
  int argsUseDefault;        // offset 0x14, size 0x4
  void* argsAddr;            // offset 0x18, size 0x4
} __OSRebootParams;          // size: 0x1C, address: 0x0

static ApploaderHeader Header ATTRIBUTE_ALIGN(32);

extern void* __OSSavedRegionStart;
extern void* __OSSavedRegionEnd;

static void* SaveStart = NULL;
static void* SaveEnd = NULL;

volatile u8 DAT_800030e2 : 0x800030e2;

extern u32 BOOT_REGION_START AT_ADDRESS(0x812FDFF0); //(*(u32 *)0x812fdff0)
extern u32 BOOT_REGION_END AT_ADDRESS(0x812FDFEC);   //(*(u32 *)0x812fdfec)
extern u32 UNK_HOT_RESET1 AT_ADDRESS(0x817ffff8);
extern u32 UNK_HOT_RESET2 AT_ADDRESS(0x817ffffc);

extern u32 __OSIsGcam;

static BOOL Prepared = FALSE;

extern void __DVDPrepareResetAsync(DVDCBCallback callback);
extern BOOL DVDCheckDisk(void);
extern BOOL DVDReadAbsAsyncForBS(DVDCommandBlock* block, void* addr, s32 length, s32 offset,
                                 DVDCBCallback callback);

asm void Run() {
  // clang-format off
  nofralloc
  sync
  isync
  mtlr r3
  blr
  // clang-format on
}

static void Callback() { Prepared = TRUE; }

void ReadApploader(OSTime time1, OSTime time2) {}

void __OSReboot(u32 resetCode, u32 bootDol) {
    OSDisableInterrupts();
    //OSClearContext();
	//OSSetCurrentContext(NULL);
    DVDInit();
    DVDSetAutoInvalidation(1);
    DVDPause();
    Prepared = 0;
    __DVDPrepareResetAsync(&Callback);
    __OSMaskInterrupts(0xffffffe0);
    __OSUnmaskInterrupts(0x400);
    OSEnableInterrupts();

    /*while (!Prepared)
    {
        if (!DVDCheckDisk() || (uVar5 = OSGetTime(), 0x80000000 < (uint)(uVar1 < (uint)uVar5 - (uint)uVar4) +
                ((int)((ulonglong)uVar5 >> 0x20) -
((uint)((uint)uVar5 < (uint)uVar4) + (int)((ulonglong)uVar4 >> 0x20)) ^ 0x80000000))) {
            __OSDoHotReset(_DAT_817ffffc);
        }
    }


    if (!__OSIsGcam && DVDGetCurrentDiskID()->is_streaming) {
        AISetStreamVolLeft(0);
        AISetStreamVolRight(0);
        DVDPrepareStreamAbsAsync(auStack_310, 0);
        uVar4 = OSGetTime();
        uVar1 = DAT_800000f8 >> 2;
        while (iVar3 = DVDGetCommandBlockStatus(auStack_310), iVar3 != 0) {
            iVar3 = DVDCheckDisk();
            if ((iVar3 == 0) ||
                (uVar5 = OSGetTime(),
                    0x80000000 <
                    (uint)(uVar1 < (uint)uVar5 - (uint)uVar4) +
                    ((int)((ulonglong)uVar5 >> 0x20) -
                        ((uint)((uint)uVar5 < (uint)uVar4) + (int)((ulonglong)uVar4 >> 0x20)) ^ 0x80000000))) {
                __OSDoHotReset(_DAT_817ffffc);
            }
        }
        AISetStreamPlayState(0);
    }

    DVDReadAbsAsyncPrio(auStack_340, &DAT_8022bbc0, 0x20, 0x2440, 0, 0);
    uVar4 = OSGetTime();
    uVar1 = DAT_800000f8 >> 2;
    while (DVDGetCommandBlockStatus(auStack_340)) {
        if (!DVDCheckDisk()) ||
            (uVar5 = OSGetTime(),
                0x80000000 <
                (uint)(uVar1 < (uint)uVar5 - (uint)uVar4) +
                ((int)((ulonglong)uVar5 >> 0x20) -
                    ((uint)((uint)uVar5 < (uint)uVar4) + (int)((ulonglong)uVar4 >> 0x20)) ^ 0x80000000))) {
            __OSDoHotReset(_DAT_817ffffc);
        }
    }
    uVar2 = DAT_8022bbd8 + 0x1fU & 0xffffffe0;

    DVDReadAbsAsyncPrio(auStack_370, 0x81300000, uVar2, DAT_8022bbd4 + 0x2460, 0, 0);
    int oldTime = OSGetTime();
    uVar1 = DAT_800000f8 >> 2;
    while (DVDGetCommandBlockStatus(auStack_370)) {
		int newTime = OSGetTime();
        if (!DVDCheckDisk() ||
                0x80000000 <
                (uint)(uVar1 < newTime - oldTime) +
                (newTime >> 0x20) - (newTime < oldTime) + (oldTime >> 0x20))) ^ 0x80000000))) {
            __OSDoHotReset(_DAT_817ffffc);
        }
    }*/

    //ICInvalidateRange(0x81300000, uVar2);
    OSDisableInterrupts();
    ICFlashInvalidate();
    Run(0x81300000);
}

/*void __OSReboot(u32 resetCode, u32 bootDol) {
  // Local variables
  OSContext exceptionContext; // r1+0x18
  char* argvToPass;           // r1+0x10
  DVDCommandBlock headerCommand;
  ApploaderHeader* header = &Header;

  OSDisableInterrupts();

  UNK_HOT_RESET1 = 0;
  UNK_HOT_RESET2 = 0;
  DAT_800030e2 = 1;
  __OSSavedRegionStart = SaveStart;
  __OSSavedRegionEnd = SaveEnd;
  OSClearContext(&exceptionContext);
  OSSetCurrentContext(&exceptionContext);
  DVDInit();
  DVDSetAutoInvalidation(TRUE);
  __DVDPrepareResetAsync(Callback);
  if (DVDCheckDisk() == FALSE) {
    __OSDoHotReset(UNK_HOT_RESET2);
  }

  __OSMaskInterrupts(OS_INTERRUPTMASK_PI);
  __OSUnmaskInterrupts(0x400);
  OSEnableInterrupts();

  do {

  } while (Prepared == 0);
  DVDReadAbsAsyncForBS(&headerCommand, header, sizeof(ApploaderHeader), 0x2440, NULL);
}*/

void OSSetSaveRegion(void* start, void* end) {
  SaveStart = start;
  SaveEnd = end;
}

void OSGetSaveRegion(void** start, void** end) {
  *start = SaveStart;
  *end = SaveEnd;
}

void OSGetSavedRegion(void** start, void** end) {
  *start = __OSSavedRegionStart;
  *end = __OSSavedRegionEnd;
}
