AS=i686-elf-as
CC=i686-elf-gcc

myos:	kernel.c boot.S linker.ld
	$(AS) boot.S -o boot.o
	$(CC) -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	$(CC) -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

start:
	qemu-system-x86_64 -kernel myos.bin

clean:
	rm *.o *.bin
