.PHONY:	all install-headers install-kernel iso start clean

CFLAGS?=-Wall -Wextra -O2

HOST=i686-elf
SYSROOT=$(PWD)/sysroot

PREFIX=
BOOTDIR=/boot
INCLUDEDIR=$(PREFIX)/include
LIBDIR=$(PREFIX)/lib

CC=$(HOST)-gcc
CC:=$(CC) --sysroot=$(SYSROOT)
# Work around because the -elf utils were not build with --with-sysroot
CC:=$(CC) -isystem=$(INCLUDEDIR)

export 

CFLAGS=$(CLFLAGS) -ffreestanding

ARCHDIR=arch

OBJ=kernel/kernel.o \
	$(ARCHDIR)/boot.o \
	$(ARCHDIR)/tty.o



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

%.o:	%.S
	@$(CC) -MD -c $< -o $@ $(CFLAGS)

%.o:	%.c
	@$(CC) -MD -c $< -o $@ $(CFLAGS) -std=gnu99

iso:	all
	@mkdir -p $(SYSROOT)/$(BOOTDIR)/grub
	@echo -e 'menuentry "myos" {\n\tmultiboot $(BOOTDIR)/myos.bin\n}'	> $(SYSROOT)/$(BOOTDIR)/grub/grub.cfg
	@grub-mkrescue -o myos.iso $(SYSROOT)

start: iso
	@qemu-system-i386 -cdrom myos.iso

clean:
	@find . -type f \( -name '*.o' -o -name '*.bin' -o -name '*.d' -o -name '*.iso' \) -exec rm {} \;
	@rm -rf $(SYSROOT)
