#ifndef MEM_H
#define MEM_H

#include <stdint.h>

void init_heap(uint32_t heap_start, uint32_t heap_end);
void* kmalloc(uint32_t size);
void kfree(void* ptr);

#endif
