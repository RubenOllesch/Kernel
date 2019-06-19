.PHONY:		all clean iso start

CC=i686-elf-gcc
CFLAGS=-ffreestanding -O2 -Wall -Wextra

ARCHDIR=arch
INCLUDEDIR=include

OBJ=kernel/kernel.o \
	$(ARCHDIR)/boot.o \
	$(ARCHDIR)/terminal.o



all:		myos.bin

myos.bin:	$(OBJ) $(ARCHDIR)/linker.ld
		@$(CC) -T $(ARCHDIR)/linker.ld -o myos.bin -ffreestanding -O2 -nostdlib -lgcc $(OBJ)
		@grub-file --is-x86-multiboot myos.bin

%.o:		%.S
		@$(CC) -MD -c $< -o $@ $(CFLAGS)

%.o:		%.c
		@$(CC) -MD -c $< -o $@ $(CFLAGS) -std=gnu99 

start:		iso
		@qemu-system-x86_64 -cdrom myos.iso

iso:		all
		@mkdir -p isodir/boot/grub
		@cp myos.bin isodir/boot/
		@cp grub.cfg isodir/boot/grub/
		@grub-mkrescue -o myos.iso isodir

clean:
		@find . -type f \( -name '*.o' -o -name '*.bin' -o -name '*.d' -o -name '*.iso' \) -exec rm {} \;
		@rm -rf isodir
