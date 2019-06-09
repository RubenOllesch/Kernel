.PHONY:		all clean iso start

AS=i686-elf-as
CC=i686-elf-gcc

OBJ=kernel.o boot.o

all:		myos.bin

myos.bin:	$(OBJ)
		@$(CC) -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc terminal.c

$(OBJ):		kernel.c boot.S linker.ld
		@$(AS) boot.S -o boot.o
		@$(CC) -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

start:		all
		@qemu-system-x86_64 -kernel myos.bin

iso:		all
		@mkdir -p isodir/boot/grub
		@cp myos.bin isodir/boot/
		@cp grub.cfg isodir/boot/grub/
		@grub-mkrescue -o myos.iso isodir

clean:
		@find . -type f \( -name '*.o' -o -name '*.bin' -o -name '*.iso' \) -exec rm {} \;
		@rm -rf isodir
