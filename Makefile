.PHONY:	all install-headers install-kernel iso start clean

CFLAGS?=-Wall -Wextra -O2

HOST=i686-elf
SYSROOT=$(PWD)/sysroot

PREFIX=
BOOTDIR=/boot
INCLUDEDIR=$(PREFIX)/include
LIBDIR=$(PREFIX)/lib

PROJECTDIRS=libc kernel

CC=$(HOST)-gcc
CC:=$(CC) --sysroot=$(SYSROOT)
# Work around because the -elf utils were not build with --with-sysroot
CC:=$(CC) -isystem=$(INCLUDEDIR)

CFLAGS:=$(CFLAGS) -ffreestanding

export 


all:	install-headers install

install-headers:
	@for dir in $(PROJECTDIRS); do \
		$(MAKE) -C $$dir install-headers; \
	done

install:
	@for dir in $(PROJECTDIRS); do \
		$(MAKE) -C $$dir install; \
	done

iso:	all
	@mkdir -p $(SYSROOT)/$(BOOTDIR)/grub
	@echo -e 'menuentry "myos" {\n\tmultiboot $(BOOTDIR)/myos.bin\n}'	> $(SYSROOT)/$(BOOTDIR)/grub/grub.cfg
	@grub-mkrescue -o myos.iso $(SYSROOT)

start: iso
	@qemu-system-i386 -cdrom myos.iso

clean:
	@find . -type f \( -name '*.o' -o -name '*.bin' -o -name '*.d' -o -name '*.iso' -o -name '*.a' \) -exec rm {} \;
	@rm -rf $(SYSROOT)
