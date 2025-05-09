/* kernel.c */
#define VIDEO_MEMORY (char*) 0xb8000
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0F

int cursor_pos = 0;

void print(const char* str) {
    char* video = VIDEO_MEMORY;
    for (int i = 0; str[i] != '\0'; ++i) {
        video[cursor_pos * 2] = str[i];
        video[cursor_pos * 2 + 1] = WHITE_ON_BLACK;
        cursor_pos++;
    }
}

void clear_screen() {
    char* video = VIDEO_MEMORY;
    for (int i = 0; i < MAX_COLS * 25; ++i) {
        video[i * 2] = ' ';
        video[i * 2 + 1] = WHITE_ON_BLACK;
    }
    cursor_pos = 0;
}

int test_var = 42;
char msg[] = "Kernel Ready\n";


void k_main() {
    const char *msg = "Type keys: ";
    char *video = (char*) 0xb8000;
    int pos = 0;

    // 초기 메시지 출력
    for (int i = 0; msg[i] != '\0'; ++i) {
        video[pos++] = msg[i];
        video[pos++] = 0x07;
    }

    while (1) {
        // 0x64 포트의 status 레지스터를 확인
        unsigned char status;
        asm volatile ("inb %1, %0" : "=a"(status) : "Nd"(0x64));
        if (status & 0x01) {
            // 0x60 포트에서 스캔코드 읽기
            unsigned char scancode;
            asm volatile ("inb %1, %0" : "=a"(scancode) : "Nd"(0x60));

            // 간단한 ascii 변환 (예: a = 0x1E)
            char c = '?';
            if (scancode == 0x1E) c = 'a';
            else if (scancode == 0x30) c = 'b';
            else if (scancode == 0x2E) c = 'c';
            else if (scancode == 0x20) c = 'd';
            else if (scancode == 0x12) c = 'e';
            else if (scancode == 0x21) c = 'f';
            else if (scancode == 0x22) c = 'g';
            else if (scancode == 0x23) c = 'h';
            else if (scancode == 0x17) c = 'i';
            else if (scancode == 0x24) c = 'j';

            // 화면에 출력
            video[pos++] = c;
            video[pos++] = 0x07;
        }
    }
}
