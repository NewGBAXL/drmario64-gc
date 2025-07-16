#ifndef MAIN_H
#define MAIN_H

#include "libultra.h"

typedef enum enum_main_no {
    /*  0 */ MAIN_NO_0,
    /*  1 */ MAIN_NO_1,
    /*  2 */ MAIN_NO_2,
    /*  3 */ MAIN_NO_3,
    /*  4 */ MAIN_NO_4,
    /*  5 */ MAIN_NO_5,
    /*  6 */ MAIN_NO_6,
    /*  7 */ MAIN_NO_7,
    /*  8 */ MAIN_NO_8, // "no controller connected"
    /*  9 */ MAIN_NO_9, // "game not designed for this system"
    /* 10 */ MAIN_NO_10, // "backup file is damaged"
} enum_main_no;


void mainproc(void *arg);

// COMMON

//extern struct NNSched B_800EB670;
extern enum_main_no main_no;
extern enum_main_no main_old;
//extern s32 __jmp_buf_tag;
extern s32 drmario_exit_flag;
extern s32 env;


#endif
