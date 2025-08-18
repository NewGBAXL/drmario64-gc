#include "PR/ultratypes.h"
#include "main1x.h"

/**
 * Original name: evs_playmax
 */
u8 evs_playmax;

/**
 * Original name: evs_gamesel
 */
enum_evs_gamesel evs_gamesel;

/**
 * Original name: evs_default_name
 */
s32 evs_default_name[8];

/**
 * Original name: evs_cfg_4p
 */
struct_evs_cfg_4p evs_cfg_4p;

/**
 * Original name: evs_select_name_no
 */
u8 evs_select_name_no[2];

/**
 * Original name: evs_game_time
 */
u32 evs_game_time;

/**
 * Original name: evs_stereo
 */
u8 evs_stereo = 1;

/**
 * Original name: evs_seqence
 */
u8 evs_seqence = 1;

/**
 * Original name: evs_seqnumb
 */
u8 evs_seqnumb = 0;

/**
 * Original name: evs_playcnt
 */
u8 evs_playcnt = 1;

/**
 * Original name: evs_keyrept
 */
u8 evs_keyrept[2] = { 0xC, 6 };

/**
 * Original name: evs_gamespeed
 */
u8 evs_gamespeed = 1;

/**
 * Original name: evs_score_flag
 */
u8 evs_score_flag = 1;

/**
 * Original name: evs_story_flg
 */
s8 evs_story_flg = 0;

/**
 * Original name: evs_story_nos
 */
s8 evs_story_no = 0;

/**
 * Original name: evs_story_level
 */
s8 evs_story_level = 1;

/**
 * Original name: evs_secret_flg
 */
u8 evs_secret_flg[2] = { 0, 0 };

/**
 * Original name: evs_one_game_flg
 */
u8 evs_one_game_flg = 0;

/**
 * Original name: evs_level_21
 */
u8 evs_level_21 = 0;

/**
 * Original name: evs_manual_no
 */
s8 evs_manual_no = EVS_MANUAL_NO_0;

/**
 * Original name: evs_high_score
 */
u32 evs_high_score = 0;

/**
 * Original name: evs_vs_count
 */
s32 evs_vs_count = 3;

/**
 * Original name: FlyingCnt
 */
u8 FlyingCnt[3] = { 0x28, 0x14, 0x14 };

/**
 * Original name: BonusWait
 */
u8 BonusWait[][3] = {
    { 2, 2, 3 },
    { 1, 1, 1 },
    { 1, 0, 1 },
};

u8 D_8008842C[] = { 0x01, 0x02, 0x02, 0x02 };

/**
 * Original name: GameSpeed
 */
s8 GameSpeed[] = { 0, 0xA, 0xF, 0x37 };

/**
 * Original name: FallSpeed
 */
u8 FallSpeed[0x38] = {
    0x27, 0x25, 0x23, 0x21, 0x1F, 0x1D, 0x1B, 0x19, 0x17, 0x15, 0x13, 0x12, 0x11, 0x10, 0xF, 0xE, 0xD, 0xC, 0xB,
    0xA,  9,    9,    8,    8,    7,    7,    6,    6,    5,    5,    5,    5,    5,    5,   5,   5,   5,   5,
    5,    5,    4,    4,    4,    4,    4,    3,    3,    3,    3,    3,    2,    2,    2,   2,   2,   1,
};

/**
 * Original name: Score1p
 */
u8 Score1p[3][6] = {
    { 1, 2, 4, 8, 0x10, 0x20 },
    { 2, 4, 8, 0x10, 0x20, 0x40 },
    { 3, 6, 0xC, 0x18, 0x30, 0x60 },
};
