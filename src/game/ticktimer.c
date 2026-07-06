#include "ticktimer.h"

static OSTick sTickTimerStart;

//8000764C
void StartTickTimer(void) {
    sTickTimerStart = OSGetTick();
}

//80007674
s32 HasTickTimerElapsed(OSTick threshold) {
    OSTick elapsed = OSGetTick() - sTickTimerStart;
    return elapsed >= threshold;
}
