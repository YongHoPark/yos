/*
 * link.ld
 */

OUTPUT_FORMAT(elf32-i386)
ENTRY(start)
SECTIONS
{
	. = 0x100000;
	.text : {*(.text)}
	.data : {*(.data)}
	.bss  : {*(.bss)}

    . = ALIGN(4K);
    end = .;   /* 커널 끝 위치 = heap 시작점 */	
}
