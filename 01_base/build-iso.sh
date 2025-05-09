#!/bin/sh
rm -f kasm.o kc.o kernel iso/boot/kernel.elf
nasm -f elf32 kernel.asm -o kasm.o
gcc -m32 -c kernel.c -o kc.o
ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
cp kernel iso/boot/kernel.elf
grub-mkrescue -o myos.iso iso/

qemu-system-i386 -cdrom myos.iso
