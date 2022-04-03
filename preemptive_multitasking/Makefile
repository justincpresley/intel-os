# Author: Justin C Presley
# Purpose: Build an OS and have a way to Boot into it.
# Functions:
#	'make'           build an os to boot to
#	'make build'     same as 'make'
#	'make install'   install the os
#	'make run'       boot the os
#	'make debug'     debug with another terminal
#       'make clean'     removes the entire os build
#       'make complete'  builds, installs, and runs the os

all: build
build: boot1 boot2

boot1: boot1.asm kernel.exe
	nasm -l boot1.list -DENTRY=0x$(shell nm kernel.exe | grep main | cut -d " " -f 1) boot1.asm
boot2: kernel.exe
	objcopy -j .text* -j .data* -j .rodata* -S -O binary kernel.exe boot2

kernel.exe: kernel_c.o kernel_asm.o screen_c.o screen_asm.o
	ld -g -melf_i386 -Ttext 0x10000 -e main -o $@ $^

# kernel
kernel_c.o: kernel.c
	gcc -g -m32 -fno-stack-protector -c -o $@ $<
kernel_asm.o: kernel.asm
	nasm -g -f elf -F dwarf -o $@ $<
# screen
screen_c.o: screen.c
	gcc -g -m32 -fno-stack-protector -c -o $@ $<
screen_asm.o: screen.asm
	nasm -g -f elf -F dwarf -o $@ $<

# All other functions of the Makefile
complete: build install run
install:
	yes | bximage -mode=create -fd=1.44M  -q a.img
	/sbin/mkdosfs a.img
	dd if=boot1 of=a.img bs=1 count=512 conv=notrunc
	mcopy -o boot2 a:BOOT2
run:
	qemu-system-i386 -boot a -fda a.img
debug:
	qemu-system-i386 -S -s -boot a -fda a.img
clean:
	rm -f *.o *.exe *.list a.img boot1 boot2