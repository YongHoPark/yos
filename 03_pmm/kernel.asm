;; kernel.asm
;; version 0.0.1

bits 32		;nasm directive
section .text
	;multiboot spec
	align 4
	dd 0x1BADB002			;magic
	dd 0x00				;flags
	dd - (0x1BADB002 + 0x00)	;checksum. m+f+c should be zero

global start
extern pmm_init      ; pmm_init(uint32_t mb_info_addr);
extern k_main	;k_main is defined in the kernel.c file

start:
	cli  ; stop interrupts

	; 전달된 multiboot info address는 ebx 레지스터에 있음
    push ebx               ; pmm_init(multiboot_info)
    call pmm_init

	call k_main

.hang:
    hlt
    jmp .hang
