#ifndef PMM_H
#define PMM_H

#pragma once
#include <stdint.h>

#define PAGE_SIZE 4096
#define MAX_MEMORY 0x1000000  // 16MB 예시
#define NUM_PAGES (MAX_MEMORY / PAGE_SIZE)

void pmm_init(uint32_t mbi_addr);
void* pmm_alloc();
void pmm_free(void* addr);


#endif
