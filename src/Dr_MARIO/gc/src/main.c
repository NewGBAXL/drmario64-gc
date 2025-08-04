/**
 * Original filename: main.c
 */

#include "main.h"

#include "unk.h"
#include "macros_defines.h"

//#include "boot_main.h"

#include "aiset.h"
#include "audio/sound.h"
//#include "buffers.h"
#include "dm_game_main.h"
#include "dm_manual_main.h"
#include "dm_title_main.h"
#include "graphic.h"
#include "joy.h"
#include "record.h"
#include "main1x.h"
#include "main_story.h"
#include "main_menu.h"
//#include "nnsched.h"

//NNSched B_800EB670;

/**
 * Original name: main_no
 */
enum_main_no main_no;

/**
 * Orignal name: main_old
 */
enum_main_no main_old;

/**
 * Original name: mainproc
 */
void mainproc(void* arg) {
    s32 uVar1;
    int iVar2;

    EepRom_DumpDataSize();
    main_no = 0;
    dm_audio_init_driver();
    gfxInit(0);
    gfxCreateGraphicThread();
    osViSetSpecialFeatures(0x4a);
    joyInit(4);
    aifFirstInit();
    while (drmario_exit_flag == 0 && __setjmp(&env)) {
        iVar2 = gc_GetResetFlag();
        if (iVar2 == 3) {
            gfxTaskStartFrameCopyFunc_set(0);
            gc_WaitForReset();
            main_no = 0;
            gfxInit(0);
            fn_2_1CEC();
            gc_PutResetNone();
        }
        uVar1 = main_no;
        n642Dolphin_AllchangeTexture();
        switch (main_no) {
        case 0:
            main_no = main11();
            break;
        case 1:
            main_no = main12();
            break;
        case 3:
            main_no = dm_title_main();
            break;
        case 4:
            main_no = dm_manual_main();
            break;
        case 5:
            main_no = dm_game_main();
            break;
        case 6:
            main_no = main_menu();
            break;
        case 7:
            main_no = main_techmes();
            break;
        case 8:
        case 9:
        case 10:
            main_no = main_boot_error();
			break;
        case 2:
            main_story();
            if ((story_proc_no == 0) || (story_proc_no == 0xc)) {
                story_proc_no = story_proc_no + 1;
                main_no = 2;
            }
            else if ((story_proc_no - 10U < 2) || (story_proc_no - 0x16U < 2)) {
                main_no = 7;
            }
            else {
                main_no = 1;
            }
            break;
        }
        main_old = uVar1;
        iVar2 = GCHandover_read(1);
        if (iVar2 != 0) {
            main_old = 3;
        }
    }
    return;
}


