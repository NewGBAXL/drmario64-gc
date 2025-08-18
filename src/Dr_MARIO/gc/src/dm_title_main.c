/**
 * Original filename: dm_title_main.c
 */

#include "dm_title_main.h"

//#include "gcc/stdlib.h"
#include "macros_defines.h"

#include "rom_offsets.h"
#include "audio/sound.h"
//#include "buffers.h"
#include "dm_game_main.h"
#include "graphic.h"
#include "joy.h"
#include "record.h"
#include "vr_init.h"
#include "main1x.h"
#include "tex_func.h"
#include "main_story.h"
//#include "nnsched.h"

 // TODO: enum?
 /**
  * Original name: title_mode_type
  */
static s32 title_mode_type;
/**
 * Original name: title_fade_count
 */
static s32 title_fade_count;
/**
 * Original name: title_fade_step
 */
static s32 title_fade_step;

/**
 * Original name: title_demo_flg
 */
s32 title_demo_flg = 0;

/**
 * Original name: title_demo_no
 */
s32 title_demo_no = 0;

/**
 * Original name: title_manual_no
 */
s32 title_manual_no = 0;

/**
 * Original name: title_exit_flag
 */
s32 title_exit_flag = 0;

/*void func_80075F30(void) {
    title_exit_flag = 0;
    title_mode_type = 0;

    title_fade_count = main_old == MAIN_NO_6 ? 0xFF : 0;
    title_fade_step = -8;
    evs_seqence = 0;
    init_title(Heap_bufferp, main_old != MAIN_NO_6);
}*/

/**
 * Original name: _stageTbl
 */
const u8 _stageTbl[] = {
    BGROMDATA_INDEX1,  BGROMDATA_INDEX2,  BGROMDATA_INDEX3,  BGROMDATA_INDEX4,  BGROMDATA_INDEX5,  BGROMDATA_INDEX6,
    BGROMDATA_INDEX7,  BGROMDATA_INDEX8,  BGROMDATA_INDEX9,  BGROMDATA_INDEX13, BGROMDATA_INDEX14, BGROMDATA_INDEX15,
    BGROMDATA_INDEX16, BGROMDATA_INDEX17, BGROMDATA_INDEX18, BGROMDATA_INDEX19, BGROMDATA_INDEX20, BGROMDATA_INDEX21,
};

/**
 * Original name: dm_title_main
 */
enum_main_no dm_title_main() {
    s32 var_s1 = (main_old == MAIN_NO_6) ? 0x99 : 0;
    u32 var_s0 = 0;
    s32 var_s2;
    s32 Gzip_bufferp = 0; //todo: fix temp

    VIGetRetraceCount();
    sgenrand(0);

    //title_fade_count = 0;
    title_exit_flag = 0;
    title_mode_type = 0;
    if (main_old == 6) {
        title_fade_count = 0xff;
    }
    title_fade_step = -8;
    var_s2 = -main_old + 6;
    evs_seqence = 0;
    //todo: fix
    //init_title(Gzip_bufferp, (void*)var_s2 - ((u32)(var_s2 == 0) + -main_old + 5));
    
    do {
        joyProcCore();
        title_fade_count = CLAMP(title_fade_count + title_fade_step, 0, 0xFF);

        switch (title_mode_type) {
        case 0:
            var_s1++;
            if (title_exit_flag == -1) {
                title_mode_type = 7;
            }
            else {
                if (var_s1 == 0x64) {
                    dm_seq_play(SEQ_INDEX_11);
                }
                if (title_exit_flag == 1) {
                    title_mode_type = 6;
                }
            }
            break;

        case 6:
        case 7:
            title_fade_step = -title_fade_step;
            if (title_mode_type == 6) {
                var_s0 = 1;
            }
            else if (title_mode_type == 7) {
                var_s0 = 2;
            }
            break;
        }

        drMarioRetrace(0);
        dm_audio_update();
        graphic_no = GRAPHIC_NO_2;
    } while (var_s0 == 0);

    dm_seq_stop();

    //todo: fix
    /*while (!dm_audio_is_stopped() || (title_fade_count < 0xFF)) {
        drMarioRetrace(0);
        dm_audio_update();
        title_fade_count = CLAMP(title_fade_count + title_fade_step, 0, 0xFF);
    }*/

    graphic_no = GRAPHIC_NO_0;
    dm_audio_update();

    if (var_s0 == 1) {
        return MAIN_NO_6;
    }

    if (var_s0 != 2) {
        return MAIN_NO_2;
    }

    if (title_demo_flg == 0) {
        u32 temp = rand();

        story_proc_no = _stageTbl[temp % ARRAY_COUNT(_stageTbl)];

        if (title_demo_no == 0) {
            evs_gamesel = ENUM_EVS_GAMESEL_4;
        }
        else if (title_demo_no == 1) {
            evs_gamesel = ENUM_EVS_GAMESEL_5;
        }
        else if (title_demo_no == 2) {
            evs_gamesel = ENUM_EVS_GAMESEL_6;
        }

        evs_gamemode = ENUM_EVS_GAMEMODE_0;

        title_demo_no++;
        if (title_demo_no >= 3) {
            title_demo_no = 0;
        }
        title_demo_flg ^= 1;
        return MAIN_NO_1;
    }

    if (title_demo_flg == 1) {
        evs_manual_no = title_manual_no;

        title_manual_no++;
        if (title_manual_no >= 4) {
            title_manual_no = 0;
        }
        title_demo_flg = 0;
        return MAIN_NO_4;
    }

    return title_demo_flg;
}

/**
 * Original name: dm_title_graphic
 */
void dm_title_graphic(void) {
    s32 color;
    s32 alpha;
	Gfx* ptr;
    
    gGfxHead = gGfxGlist[gCurrentFramebufferIndex];

    ptr = 0;//&B_800FAE80[gCurrentFramebufferIndex];
    //gSPSegment(gGfxHead++, 0x00, NULL);
    S2RDPinitRtn(true);
    S2ClearCFBRtn(true);

    //gSPDisplayList(gGfxHead++, S2Spriteinit_dl);
    //gDPSetScissor(gGfxHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);

    title_exit_flag = demo_title(&gGfxHead, evs_level_21 != 0);
    color = title_exit_flag ? 0 : 0xFF;

    alpha = CLAMP((title_fade_count - 127) * 1.2 + 127, 0.0, 255.0);
    if (alpha > 0) {
        FillRectRGBA(&gGfxHead, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, color, color, color, alpha);
    }

    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);
    osWritebackDCacheAll();

    gfxTaskStart(ptr, gGfxGlist[gCurrentFramebufferIndex],
        (gGfxHead - gGfxGlist[gCurrentFramebufferIndex]) * sizeof(Gfx), 0, 0/*OS_SC_SWAPBUFFER*/);
}

#include "msg/dm_title_main.msg"

/**
 * Original name: main_boot_error
 */
enum_main_no main_boot_error() {
    void* sp58;
    MessageWnd* messageWnd = 0;//Gzip_bufferp + 0xfU & 0xfffffff0; //ALIGN_PTR(Heap_bufferp);
    bool var_s1 = true;

    sp58 = messageWnd + 1;
    bzero(messageWnd, sizeof(MessageWnd));

    switch (main_no) {
    case MAIN_NO_8:
        msgWnd_init(messageWnd, &sp58, 0x40, 5, 0x40, 0x60);
        msgWnd_addStr(messageWnd, _mesBootContErr);
        break;

    case MAIN_NO_9:
        msgWnd_init(messageWnd, &sp58, 0x40, 5, 0x40, 0x72);
        msgWnd_addStr(messageWnd, STR_800B32A8);
        break;

    case MAIN_NO_10:
        msgWnd_init(messageWnd, &sp58, 0x40, 5, 0x28, 0x6C);
        msgWnd_addStr(messageWnd, _mesBootCSumErr);
        break;
    }

    msgWnd_skip(messageWnd);

    while (var_s1) {
        joyProcCore();
        msgWnd_update(messageWnd);
        if ((main_no == MAIN_NO_10) && (gControllerPressedButtons[main_joy[0]] & A_BUTTON)) {
            var_s1 = false;
            dm_snd_play(SND_INDEX_70);
        }
        dm_audio_update();
        graphic_no = GRAPHIC_NO_7;
        drMarioRetrace(0);
    }

    graphic_no = GRAPHIC_NO_0;

    if (main_no == MAIN_NO_10) {
        EepRom_WriteAll((void*)NULL, (void*)NULL, 0, 0, 0);
    }

    return MAIN_NO_3;
}

/**
 * Original name: graphic_boot_error
 */
/*void graphic_boot_error(void) {
    MessageWnd* ptr;

    gGfxHead = gGfxGlist[gfx_gtask_no];
    //ptr = ALIGN_PTR(&Heap_bufferp); //todo: fix
    F3RCPinitRtn();
    F3ClearFZRtn(true);
    msgWnd_draw(ptr, &gGfxHead);

    gDPFullSync(gGfxHead++);
    gSPEndDisplayList(gGfxHead++);

    osWritebackDCacheAll();
    //gfxTaskStart(&B_800FAE80[gfx_gtask_no], gGfxGlist[gfx_gtask_no], (gGfxHead - gGfxGlist[gfx_gtask_no]) * sizeof(Gfx),
    //    0, OS_SC_SWAPBUFFER);
}*/

extern Gzip_bufferp;
extern gp;

void graphic_boot_error(void)
{
    s32 /*undefined4**/ puVar1;
    s32 /*undefined4**/ puVar2;
    u32 uVar3;
    
    uVar3 = Gzip_bufferp + 0xf;
    //gp = 0;//(undefined4*)(gfx_glist + gfx_gtask_no * 0x12000);
    F3RCPinitRtn();
    F3ClearFZRtn(true);
    //msgWnd_draw(uVar3 & 0xfffffff0, &gp);
    puVar1 = gp;
    puVar2 = gp + 2;
    //*gp = 0xe9000000;
    gp = puVar2;
    //puVar1[1] = 0;
    puVar1 = gp;
    puVar2 = gp + 2;
    //*gp = 0xdf000000;
    gp = puVar2;
    //puVar1[1] = 0;
    osWritebackDCacheAll();
    //uVar3 = (int)gp - (int)(gfx_glist + gfx_gtask_no * 0x12000);
    //gfxTaskStart(gfx_glist + gfx_gtask_no * 0x12000,
    //    (((int)uVar3 >> 3) + (uint)((int)uVar3 < 0 && (uVar3 & 7) != 0)) * 8, 0, 0x40);
    return;
}
