#include "libultra.h"
#include "audio/sound.h"
#include "snd_seq.h"

const u8 _charSE_tbl[] = {
    SND_INDEX_94 - 3, SND_INDEX_84 - 3, SND_INDEX_38 - 3, SND_INDEX_43 - 3, SND_INDEX_48 - 3,
    SND_INDEX_18 - 3, SND_INDEX_28 - 3, SND_INDEX_23 - 3, SND_INDEX_3 - 3,  SND_INDEX_8 - 3,
    SND_INDEX_13 - 3, SND_INDEX_33 - 3, SND_INDEX_53 - 3, SND_INDEX_89 - 3, SND_INDEX_99 - 3,
};

void dm_audio_set_stereo(s32 mode) {
    if (mode == 1) {
        gc_soundSetOutputMode(1);
    }
    else {
        gc_soundSetOutputMode(0);
    }
}

void dm_audio_init_driver(void) {
    sound_song_seqNo = 0xffffffff;
    sound_song_id = 0xffffffff;
    DAT_002d4284 = 0xffffffff;
    DAT_002d427c = 0xffffffff;
    return;
}

//todo
void dm_audio_update(void) {}

void dm_audio_stop(void) {
    gc_soundAllStop();
    return;
}

void dm_audio_is_stopped(void) {
    gc_soundAllStop_check();
    return;
}

void dm_seq_play(u32 arg0) {
    _dm_seq_play(0, arg0);
    return;
}

void _dm_seq_play(s32 arg0, SeqIndex seqIndex) {
    _dm_seq_play_fade(arg0, seqIndex, 0);
}

void dm_seq_play_fade(SeqIndex seqIndex, s32 arg1) {
    _dm_seq_play_fade(0, seqIndex, arg1);
}

s32 _dm_seq_play_fade(s32 arg0, s32 arg1, s32 arg2) {
    s32 iVar1;
    u32 uVar2;

    if (arg1 != (&sound_song_seqNo)[arg0]) {
        iVar1 = (arg2 * 1000) / 0x3c + (arg2 * 1000 >> 0x1f);
        uVar2 = iVar1 - (iVar1 >> 0x1f);
        _gc_songFadeSong((&sound_song_id)[arg0], 0, uVar2 & 0xffff);
        (&sound_song_seqNo)[arg0] = arg1;
        *(u32*)((s32)&sound_song_frame + arg0 * 4) = uVar2;
    }
    return arg0;
}

void dm_seq_play_in_game(s32 arg0) {
    _dm_seq_play_in_game(0, arg0);
    return;
}


void _dm_seq_play_in_game(s32 arg0, s32 arg1) {
    char evs_seqence = 0; //gc, fix
    
    if (evs_seqence == '\0') {
        if ((arg1 < 10) && (-1 < arg1)) {
            _dm_seq_stop(arg0);
        }
        else if (arg1 != (&sound_song_seqNo)[arg0]) {
            _gc_songFadeSong((&sound_song_id)[arg0], 0, 0);
            (&sound_song_seqNo)[arg0] = arg1;
            *(s32*)((s32)&sound_song_frame + arg0 * 4) = 0;
        }
    }
    else if (arg1 != (&sound_song_seqNo)[arg0]) {
        _gc_songFadeSong((&sound_song_id)[arg0], 0, 0);
        (&sound_song_seqNo)[arg0] = arg1;
        *(s32*)((s32)&sound_song_frame + arg0 * 4) = 0;
    }
    return;
}

void dm_seq_stop(void) {
    _dm_seq_stop(0);
    fn_2_2153C(0);
    return;
}

void _dm_seq_stop(s32 arg0) {
    s32 uVar1;

    uVar1 = (&sound_sound_id)[arg0];
    _gc_songStop(uVar1, uVar1);
    (&sound_sound_id)[arg0] = 0xffffffff;
    return;
}

void fn_2_2153C(int arg0) {
    if ((int)(&sound_song_id)[arg0] < 0) {
        return;
    }
    (&sound_song_id)[arg0] = -1;
    return;
}

void dm_seq_set_volume(s32 arg0) {
    _dm_seq_set_volume(0, arg0);
    return;
}

void _dm_seq_set_volume(s32 arg0, s32 volume) {
    if (volume != 0) {
        volume -= 1;
    }
    _gc_songFadeSong((&sound_song_id)[arg0], volume & 0xff, 0);
    return;
}

s32 _dm_seq_is_stopped(s32 arg0) {
    u32 uVar1;
    s32 iVar2;

    iVar2 = _gc_songGetValid((&sound_song_id)[arg0], (&sound_song_id)[arg0]);
    uVar1 = countLeadingZeros(-iVar2);
    return uVar1 >> 5;
}

void dm_snd_play(s32 arg0) {
    s32* piVar1;
    s32 iVar2;

    /*if (subproc_nuGfxFunc_cnt != bak_subproc_nuGfxFunc_cnt$195) {
        dm_snd_play_idx$196 = 0;
    }
    bak_subproc_nuGfxFunc_cnt$195 = subproc_nuGfxFunc_cnt;
    if (dm_snd_play_idx$196 < 4) {
        piVar1 = &dm_snd_play_buf$194;
        iVar2 = dm_snd_play_idx$196;
        if (0 < dm_snd_play_idx$196) {
            do {
                if (arg0 == *piVar1) {
                    return;
                }
                piVar1 = piVar1 + 1;
                iVar2 = iVar2 + -1;
            } while (iVar2 != 0);
        }
        piVar1 = &dm_snd_play_buf$194 + dm_snd_play_idx$196;
        dm_snd_play_idx$196 = dm_snd_play_idx$196 + 1;
        *piVar1 = arg0;
        _gc_sePlay(arg0, 0xff, 0xff);
    }*/
}


void dm_snd_play_in_game(s32 arg0)

{
    s32* piVar1;
    s32 iVar2;

	/*s32 evs_gamespeed = 0; //gc, fix

    if (evs_gamespeed < 6) {
        if (subproc_nuGfxFunc_cnt != bak_subproc_nuGfxFunc_cnt$195) {
            dm_snd_play_idx$196 = 0;
        }
        bak_subproc_nuGfxFunc_cnt$195 = subproc_nuGfxFunc_cnt;
        if (dm_snd_play_idx$196 < 4) {
            piVar1 = &dm_snd_play_buf$194;
            iVar2 = dm_snd_play_idx$196;
            if (0 < dm_snd_play_idx$196) {
                do {
                    if (arg0 == *piVar1) {
                        return;
                    }
                    piVar1 = piVar1 + 1;
                    iVar2 = iVar2 + -1;
                } while (iVar2 != 0);
            }
            piVar1 = &dm_snd_play_buf$194 + dm_snd_play_idx$196;
            dm_snd_play_idx$196 = dm_snd_play_idx$196 + 1;
            *piVar1 = arg0;
            _gc_sePlay(arg0, 0xff, 0xff);
        }
    }*/
}


void dm_snd_play_strange_sound(void) {
    s32* piVar1;
    s32 iVar2;
    s32* piVar3;
    u32 uVar4;
    u32 uVar5;
    s32 iVar6;
    s32 local_28[4];

    /*for (uVar4 = 0; uVar4 < 4; uVar4++) {
        iVar6 = rand();
        iVar2 = iVar6 / 0xf + (iVar6 >> 0x1f);
        local_28[uVar4] = iVar6 + (iVar2 - (iVar2 >> 0x1f)) * -0xf;
        piVar1 = local_28;
        uVar5 = uVar4;
        if (0 < (s32)uVar4) {
            do {
                if (local_28[uVar4] == *piVar1) {
                    uVar4 = uVar4 - 1;
                    break;
                }
                piVar1 = piVar1 + 1;
                uVar5 = uVar5 - 1;
            } while (uVar5 != 0);
        }
    }
    piVar1 = local_28;
    uVar4 = 0;
    do {
        iVar2 = (byte)_charSE_tbl[*piVar1] + 3;
        if (subproc_nuGfxFunc_cnt != bak_subproc_nuGfxFunc_cnt$195) {
            dm_snd_play_idx$196 = 0;
        }
        bak_subproc_nuGfxFunc_cnt$195 = subproc_nuGfxFunc_cnt;
        if (dm_snd_play_idx$196 < 4) {
            piVar3 = &dm_snd_play_buf$194;
            iVar6 = dm_snd_play_idx$196;
            if (0 < dm_snd_play_idx$196) {
                do {
                    if (iVar2 == *piVar3) goto LAB_00032a14;
                    piVar3 = piVar3 + 1;
                    iVar6 = iVar6 + -1;
                } while (iVar6 != 0);
            }
            piVar3 = &dm_snd_play_buf$194 + dm_snd_play_idx$196;
            dm_snd_play_idx$196 = dm_snd_play_idx$196 + 1;
            *piVar3 = iVar2;
            _gc_sePlay(iVar2, 0xff, 0xff);
        }
    LAB_00032a14:
        uVar4 += 1;
        piVar1 += 1;
    } while (uVar4 > 3);*/
}

