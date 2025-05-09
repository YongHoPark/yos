ISO = myos.iso
BUILD = kernel
KERNEL_ELF = iso/boot/kernel.elf

all: $(ISO)

$(ISO): kernel.asm kernel.c link.ld
	rm -f kasm.o kc.o kernel $(KERNEL_ELF)
	nasm -f elf32 kernel.asm -o kasm.o
	gcc -m32 -c kernel.c -o kc.o
	ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
	mkdir -p iso/boot
	cp kernel $(KERNEL_ELF)
	grub-mkrescue -o $(ISO) iso/

run: all
	qemu-system-i386 -cdrom $(ISO)

clean:
	rm -f *.o kernel $(ISO) $(KERNEL_ELF)
