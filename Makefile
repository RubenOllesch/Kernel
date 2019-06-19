.PHONY:		all install-headers install-kernel iso start clean

export HOST=i686-elf

export CC=$(HOST)-gcc
export CFLAGS=-Wall -Wextra -O2

export PREFIX=
export INCLUDEDIR=$(PREFIX)/include
export BOOTDIR=/boot
export LIBDIR=$(PREFIX)/lib

export SYSROOT=$(PWD)/sysroot
export CC:=$(CC) --sysroot=$(SYSROOT)

# Work around because the -elf utils were not build with --with-sysroot
export CC:=$(CC) -isystem=$(INCLUDEDIR)


CFLAGS?=
CFLAGS=$(CLFLAGS) -ffreestanding

ARCHDIR=arch

OBJ=kernel/kernel.o \
	$(ARCHDIR)/boot.o \
	$(ARCHDIR)/terminal.o



all:	install-headers install-kernel

install-headers:
		@mkdir -p $(SYSROOT)/$(INCLUDEDIR)
		@cp -R --preserve=timestamps include/. $(SYSROOT)/$(INCLUDEDIR)/.

install-kernel: myos.bin
		@mkdir -p $(SYSROOT)/$(BOOTDIR)
		@cp myos.bin $(SYSROOT)/$(BOOTDIR)

myos.bin:	$(OBJ) $(ARCHDIR)/linker.ld
		@$(CC) -T $(ARCHDIR)/linker.ld -o myos.bin -ffreestanding -O2 -nostdlib -lgcc $(OBJ)
		@grub-file --is-x86-multiboot myos.bin

%.o:		%.S
		@$(CC) -MD -c $< -o $@ $(CFLAGS)

%.o:		%.c
		@$(CC) -MD -c $< -o $@ $(CFLAGS) -std=gnu99

iso:	all
		@mkdir -p isodir/boot/grub
		@cp $(SYSROOT)/$(BOOTDIR)/myos.bin isodir/boot/
		@cp grub.cfg isodir/boot/grub/
		@grub-mkrescue -o myos.iso isodir

start: iso
		@qemu-system-i386 -cdrom myos.iso

clean:
		@find . -type f \( -name '*.o' -o -name '*.bin' -o -name '*.d' -o -name '*.iso' \) -exec rm {} \;
		@rm -rf isodir sysroot
