/**
 * Original filename: joy.c
 */

#include "joy.h"

 /**
  * Original name: joycur
  */
u16 joycur[MAXCONTROLLERS + 1];

/**
 * Original name: joyupd
 */
u16 gControllerPressedButtons[MAXCONTROLLERS + 1];

u16 gControllerPrevHoldButtons[MAXCONTROLLERS + 1];

u16 gControllerHoldButtons[MAXCONTROLLERS + 1];

/**
 * Original name: joycnt
 */
u16 joycnt[MAXCONTROLLERS][0x10];

/**
 * Original name: joyflg
 */
u16 joyflg[MAXCONTROLLERS];

/**
 * Original name: joygam
 */
u16 joygam[MAXCONTROLLERS];

/**
 * Original name: joygmf
 */
u8 joygmf[MAXCONTROLLERS];

/**
 * Original name: link_joy
 */
u8 link_joy[MAXCONTROLLERS];

/**
 * Original name: main_joy
 */
u8 main_joy[MAXCONTROLLERS];

/**
 * Original name: joycur1
 */
u16 joycur1;

/**
 * Original name: joycur2
 */
u16 joycur2;

OSContStatus B_800F5358[4];
//OSMesgQueue B_800F3E38;
//OSMesg B_800F3E60[1];
OSContPad B_800EB4D8[MAXCONTROLLERS];

/**
 * Original filename: joyInit
 */
s32 joyInit(s32 arg0 /*num pads, unused*/) {
    //new

    s32 i = 0;
    
    //joycur = 0;
    //joyupd = 0;
    //joyold = 0;
    //joynew = 0;

    for (i = 0; i < ARRAY_COUNT(gControllerPressedButtons); i++) {
        joycur[i] = 0;
        gControllerPressedButtons[i] = 0;
        gControllerPrevHoldButtons[i] = 0;
        gControllerHoldButtons[i] = 0;
    }
    
    for (i = 2; i != 0; i--) {
        s32 j;

        for (j = 0; j < ARRAY_COUNT(joycnt[i]); j++) {
            joycnt[i][j] = 0;
        }

        joyflg[i] = 0;
        joygam[i] = 0;
        joygmf[i] = 0;
    }

    joycur1 = 0x14;
    joycur2 = 4;
    nuContInit();
    joyResponseCheck();
    return 4; //todo: change to void ret
}

/**
 * Original filename: joyProcCore
 */
void joyProcCore(void) {
    u16 i;

    /*bool*/ int pressingOppositeDirections = 0 /*false */ ;

    nuContDataGetExAll(B_800EB4D8);

    for (i = 0; i < ARRAY_COUNT(joycnt); i++) {
        u16 j;
        u32 mask;
        u32 button = B_800EB4D8[i].button;

        gControllerHoldButtons[i] = button;

        gControllerPressedButtons[i] = ~gControllerPrevHoldButtons[i];
        gControllerPressedButtons[i] &= button;

        joycur[i] = 0;

        for (j = 0, mask = 0x8000; j < ARRAY_COUNT(joycnt[i]); j++, mask >>= 1) {
            if (joyflg[i] & mask) {
                if (mask & gControllerHoldButtons[i]) {
                    joycnt[i][j]++;
                    if ((joycnt[i][j] == 1) ||
                        ((joycnt[i][j] >= joycur1) && (((joycnt[i][j] - joycur1) % joycur2) == 0))) {
                        joycur[i] |= mask;
                    }
                }
                else {
                    joycnt[i][j] = 0;
                }
            }
        }

        gControllerPrevHoldButtons[i] = gControllerHoldButtons[i];
    }
}

/**
 * Original filename: joyCursorFastSet
 */
void joyCursorFastSet(u16 mask, u8 index) {
    s32 var_a0 = mask;
    s32 j;

    for (j = ARRAY_COUNT(joycnt[0]) - 1; j >= 0; j--) {
        if (var_a0 & 1) {
            break;
        }

        var_a0 >>= 1;
    }
    joycnt[index][j] = joycur1 + joycur2 - 1;
}

/**
 * Returns the amount of connected controllers
 *
 * Original filename: joyResponseCheck
 */
s32 joyResponseCheck(void) {
    s32 connectedControllers = 0;
    OSContStatus padStatus[MAXCONTROLLERS];
    s8 j;
    s8 i;

    nuContQueryRead(padStatus);

    for (i = 0; i < 4; i++) {
        main_joy[i] = 4;
    }

    j = 0;
    for (i = 0; i < ARRAY_COUNT(padStatus); i++) {
        link_joy[i] = 0 /*false*/;

        switch (padStatus[i].errno) {
        case CONT_NO_RESPONSE_ERROR:
            break;

        default:
            if ((padStatus[i].type & CONT_TYPE_MASK) == CONT_TYPE_NORMAL) {
                link_joy[i] = 1 /*true*/;
                main_joy[j] = i;
                connectedControllers++;
                j++;
            }
        }
    }

    /*for (i = 0; i < ARRAY_COUNT(padStatus); i++) {
        *puVar1 = 0;
        if ((*puVar2 & 1) != 0) {
            *puVar1 = 1;
            connectedControllers++;
            *pcVar3 = cVar4;
            pcVar3 += 1;
        }
        puVar1 += 1;
        puVar2 += 2;
    }*/

    return connectedControllers;
}
