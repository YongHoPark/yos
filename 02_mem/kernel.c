#include "mem.h"

void k_main() {
    extern uint32_t end;
    init_heap((uint32_t)&end, 0x200000);

    char *a = (char*)kmalloc(64);
    char *b = (char*)kmalloc(128);

    a[0] = 'X'; b[0] = 'Y';

    kfree(a);  // free 후 재사용
    char *c = (char*)kmalloc(64);  // a와 동일한 블록 재사용됨

    const char *msg = "Memory alloc ok\n";
    char *video = (char*) 0xb8000;
    for (int i = 0; msg[i]; ++i) {
        video[i * 2] = msg[i];
        video[i * 2 + 1] = 0x07;
    }

    while (1) {}
}
