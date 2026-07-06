#ifndef TICKTIMER_H
#define TICKTIMER_H

#include <types.h>
#include <dolphin/os.h>

//8000764C
void StartTickTimer(void);

//80007674
s32 HasTickTimerElapsed(OSTick threshold);

#endif