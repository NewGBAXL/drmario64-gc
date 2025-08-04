#include "constract.h"
#include "libultra.h"

#include "drmario_gc.h"

extern s32 _ctors;

void _prolog(void) {
    func_ptr* p = 0;//&_ctors;
    while (*p != NULL) {
        p++;
    }
    main();
}

void _epilog(void) {
    func_ptr* p = 0;//&_dtors;
    while (*p != NULL) {
        p++;
    }
}

void _unresolved(void) {
    return;
}
