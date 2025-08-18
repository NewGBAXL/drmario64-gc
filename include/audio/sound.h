#ifndef SOUND_H
#define SOUND_H

#include "libultra.h"
#include "snd_seq.h"

typedef struct SndEntry {
    /* 0x0 */ u8 number;
    /* 0x1 */ s8 offset;
    /* 0x2 */ u8 unk_2;
    /* 0x3 */ u8 priority;
    /* 0x4 */ u8 unk_4;
    /* 0x5 */ u8 volume;
} SndEntry; // size = 0x6

typedef struct struct_800FACE0_unk_08 {
    /* 0x0 */ const SndEntry* sndEntry;
    /* 0x4 */ s32 index;
    /* 0x8 */ u8 unk_8;
} struct_800FACE0_unk_08; // size = 0xC

typedef struct struct_800FACE0 {
    /* 0x00 */ SeqIndex seqIndex[2];
    /* 0x08 */ struct_800FACE0_unk_08 unk_08[4];
    /* 0x38 */ struct_800FACE0_unk_08* unk_38[4];
} struct_800FACE0; // size >= 0x3C


void dm_audio_set_stereo(s32 mode);
void dm_audio_init_driver(void);
void dm_audio_update(void);
void dm_audio_stop(void);
void dm_audio_is_stopped(void);
void dm_seq_play(u32 arg0);
void _dm_seq_play(s32 arg0, SeqIndex seqIndex);
void dm_seq_play_fade(SeqIndex seqIndex, s32 arg1);
s32 _dm_seq_play_fade(s32 arg0, SeqIndex seqIndex, s32 arg2);
void dm_seq_play_in_game(s32 arg0);
void _dm_seq_play_in_game(s32 arg0, s32 arg1);
void dm_seq_stop(void);
void _dm_seq_stop(s32 arg0);
void fn_2_2153C(int arg0);
void dm_seq_set_volume(s32 arg0);
void _dm_seq_set_volume(s32 arg0, s32 volume);
s32 _dm_seq_is_stopped(s32 arg0);

// data
struct_800FACE0 sound_song_id;
struct_800FACE0 sound_song_seqNo;
u32 DAT_002d4284;
u32 DAT_002d427c;
u32 sound_song_frame;

extern const u8 _charSE_tbl[];
extern subproc_nuGfxFunc_cnt;
extern bak_subproc_nuGfxFunc_cnt_195;
extern s32 dm_snd_play_idx_196;
extern s32 dm_snd_play_buf_194;

#endif
