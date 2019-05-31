myos:	kernel.c boot.S linker.ld
	i686-elf-as boot.S -o boot.o
	i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

start:
	qemu-system-x86_64 -kernel myos.bin

clean:
	rm *.o *.bin