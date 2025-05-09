#include "pmm.h"

extern void pmm_init(uint32_t mb_info);

void k_main() {

    /*
    void* mem = pmm_alloc();

    const char *msg = "pmm alloc ok\n";
    char *video = (char*) 0xb8000;
    for (int i = 0; msg[i]; ++i) {
        video[i * 2] = msg[i];
        video[i * 2 + 1] = 0x07;
    }

    pmm_free(mem);
    */

    while (1) {}
}
