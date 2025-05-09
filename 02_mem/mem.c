#include "mem.h"

typedef struct FreeBlock {
    uint32_t size;
    struct FreeBlock* next;
} FreeBlock;

static uint32_t heap_start;
static uint32_t heap_end;
static uint32_t heap_curr;

static FreeBlock* free_list = 0;

void init_heap(uint32_t start, uint32_t end) {
    heap_start = start;
    heap_end = end;
    heap_curr = start;
    free_list = 0;
}

void* kmalloc(uint32_t size) {
    // 정렬
    if (size % 8 != 0)
        size = (size + 7) & ~7;

    // 1. free_list에서 재사용 가능한 블록이 있는지 확인
    FreeBlock **prev = &free_list;
    FreeBlock *curr = free_list;
    while (curr) {
        if (curr->size >= size) {
            *prev = curr->next;
            return (void*)(curr + 1); // 헤더 다음
        }
        prev = &curr->next;
        curr = curr->next;
    }

    // 2. 새로운 블록을 heap에서 할당
    if (heap_curr + size + sizeof(FreeBlock) > heap_end)
        return 0; // out of memory

    FreeBlock* block = (FreeBlock*)heap_curr;
    block->size = size;
    heap_curr += size + sizeof(FreeBlock);
    return (void*)(block + 1);
}

void kfree(void* ptr) {
    if (!ptr) return;

    FreeBlock* block = ((FreeBlock*)ptr) - 1;
    block->next = free_list;
    free_list = block;
}
