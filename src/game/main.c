#include <types.h>

extern s32 lbl_801F9C08[];

u32 OSGetResetCode(void);
s32 *fn_80006838(const char*);
s32 fn_800068EC(void);
void fn_80006994(void);
void fn_80006D04(s32);
void fn_80006D5C(void);
void fn_80006CF4(void);
void fn_80006DD8(void);
void fn_8000C0B8(void);
void fn_8000C298(void);
void fn_80012448(void);
s32 fn_80012854(void);
void fn_800128C4(void);
s32 fn_800158C4(void);
void fn_800160CC(const char *, s32, s32, s32);
s32 *fn_800160FC(void);
void fn_80018CD0(void);
void fn_80018D00(int, int);
void fn_800196A8(int);
void fn_8001970C(void);
void fn_80019C68(void);
void fn_80019C78(void);
void fn_80019D00(void);
void fn_8001A22C(void);
u32 fn_800489E8(void);


s32 lbl_800C6C40[10];
s32 lbl_800C6C68[3];

int main(void) {
    s32 var_r30;
    
    lbl_800C6C68[0] = var_r30 = 0;
    if ((OSGetResetCode() + 0x80000000) == 0) {
        var_r30 = 1;
    }
    lbl_800C6C68[1] = var_r30;
    var_r30 = 0;
    if ((lbl_800C6C68[1] != 0) && (fn_800489E8() == 1)) {
        var_r30 = 1;
    }
    lbl_800C6C68[2] = var_r30;
    fn_800128C4();
    fn_80018CD0();
    fn_80018D00(1, 0);
    fn_80018D00(7, 0);
    lbl_801F9C08[0] = 1;
    fn_800196A8(1);
    fn_8001970C();
    fn_80006DD8();
    
    return 0;
}

s32 *fn_80006838(const char *arg0) {
    s32 var_r31;

    fn_800160CC(arg0, 0, 0, 0);
    while (1) {
        var_r31 = fn_800158C4();
        if (var_r31 == 0x28) {
            fn_800160CC(arg0, 0, 0, 0);
            var_r31 = 0x24;
        }
        fn_80006D04(var_r31);
        if (var_r31 == 36) {
            if (fn_80012854() == 0) {
                fn_8001A22C();
                continue;
            }
            fn_80019D00();
            if (fn_80012854() != 0x18) {
                continue;
            }
            while (1) {}
        } else if (var_r31 != 0) {
            return NULL;
        } else {
            return fn_800160FC();
        }
    }
}

s32 fn_800068EC(void) {
    s32 i;
    s32 *temp_r3;

    fn_80019C68();
    temp_r3 = fn_80006838("/ycookie.szp");
    for (i = 0; i < 4; i++) {
        lbl_800C6C40[i] = 0;
        lbl_800C6C40[i] = temp_r3[i];
    }
    fn_80012448();
    fn_80019C78();
    return 0;
}

s32 lbl_800BDD38[2] = { 1, 0 };

void fn_80006968(void) {
    fn_80006CF4();
    lbl_800BDD38[0] = 0;
}

void fn_80006DD8(void) {
    s32 *temp = lbl_800C6C68;
    if (temp[2] != 0) {
        fn_8000C298();
    } else {
        fn_8000C0B8();
    }
    fn_800068EC();
    fn_80006D5C();
    while (1) fn_80006994();
}
