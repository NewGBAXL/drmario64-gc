#include <game/memory.h>
#include <types.h>
#include <dolphin/os/OSAlloc.h>

int alloc_counter = 0;

void DoMalloc(int size) {
    if (OSAllocFromHeap(__OSCurrHeap, size)) {
        alloc_counter += 1;
    }
}

void DoFree(void* ptr) {
    if (ptr != 0) {
        OSFreeToHeap(__OSCurrHeap, ptr);
        alloc_counter -= 1;
    }
}

int DoGetRestAlloc(void) {
    return alloc_counter;
}
