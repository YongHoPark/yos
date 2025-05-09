#include "pmm.h"
#include <stdint.h>
#include <string.h>

extern uint32_t end;  // linker.ld에서 정의한 end 심볼

#define PAGE_SIZE 4096
#define MAX_PAGES 1024
#define BITMAP_SIZE (MAX_PAGES / 8)  // 비트맵 크기 (페이지 수에 맞는 비트맵 크기)

// 비트맵과 메모리 할당 상태 관리
uint8_t *page_bitmap = NULL;  // 페이지 비트맵
uint32_t memory_start = 0;    // 할당 가능한 메모리의 시작 주소

// 비트맵에서 비트 설정 및 검사
static inline void set_bit(uint8_t* bitmap, uint32_t bit) {
    bitmap[bit / 8] |= (1 << (bit % 8));
}

static inline int test_bit(uint8_t* bitmap, uint32_t bit) {
    return bitmap[bit / 8] & (1 << (bit % 8));
}

// PMM 초기화
void pmm_init(uint32_t mmap_addr) {
    // mmap_addr에서 메모리 맵 정보 읽어오기
    uint32_t mmap_length = *(uint32_t*)(mmap_addr + 4);  // 멀티부트 정보에서 메모리 맵의 길이

    // 비트맵과 메모리 할당 영역을 설정하는 코드 (이전과 동일)
    uint32_t mmap_end = mmap_addr + mmap_length;
    for (uint32_t i = mmap_addr; i < mmap_end; i += 24) {  // 24는 멀티부트 메모리 맵 항목의 크기 (24 bytes)
        uint32_t base_addr = *(uint32_t*)(i);               // 베이스 주소
        uint32_t length = *(uint32_t*)(i + 4);              // 길이
        uint32_t type = *(uint32_t*)(i + 8);                // 타입

        // usable 영역만 처리
        if (type == 1) {  // type 1은 usable 메모리
            uint32_t start_page = base_addr / PAGE_SIZE;
            uint32_t end_page = (base_addr + length) / PAGE_SIZE;

            for (uint32_t page = start_page; page < end_page; page++) {
                set_bit(page_bitmap, page);
            }
        }
    }


    const char *msg = "pmm_init ok\n";
    char *video = (char*) 0xb8000;
    for (int i = 0; msg[i]; ++i) {
        video[i * 2] = msg[i];
        video[i * 2 + 1] = 0x07;
    }
}

// 메모리 할당 함수 (pmm_alloc)
void* pmm_alloc() {
    for (uint32_t page = 0; page < MAX_PAGES; page++) {
        if (!test_bit(page_bitmap, page)) {  // 사용 가능한 페이지를 찾음
            set_bit(page_bitmap, page);  // 해당 페이지를 사용 중으로 설정
            return (void*)(memory_start + (page * PAGE_SIZE));  // 비트맵 이후부터 할당
        }
    }

    const char *msg = "pmm_alloc ok\n";
    char *video = (char*) 0xb8000;
    for (int i = 0; msg[i]; ++i) {
        video[i * 2] = msg[i];
        video[i * 2 + 1] = 0x07;
    }

    return NULL;  // 더 이상 할당할 페이지가 없음
}

// 메모리 해제 함수 (pmm_free)
void pmm_free(void* ptr) {
    uint32_t page = ((uint32_t)ptr - memory_start) / PAGE_SIZE;

    if (page < MAX_PAGES) {
        // 페이지 비트맵에서 해당 페이지를 사용 가능으로 설정
        set_bit(page_bitmap, page);
    }


    const char *msg = "pmm_free ok\n";
    char *video = (char*) 0xb8000;
    for (int i = 0; msg[i]; ++i) {
        video[i * 2] = msg[i];
        video[i * 2 + 1] = 0x07;
    }
}
