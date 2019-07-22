CFLAGS?=-O2 -Wall -Wextra -Wpedantic

TOOLCHAIN=$(PWD)/toolchain
TOOLCHAINPATH=$(TOOLCHAIN)/bin

HOST=i686-elf
SYSROOT=$(PWD)/sysroot

PREFIX=
BOOTDIR=/boot
INCLUDEDIR=$(PREFIX)/include
LIBDIR=$(PREFIX)/lib

PROJECTDIRS=libc kernel


AR=$(TOOLCHAINPATH)/$(HOST)-ar
CC=$(TOOLCHAINPATH)/$(HOST)-gcc

CC:=$(CC) --sysroot=$(SYSROOT)
# Work around because the -elf utils were not build with --with-sysroot
CC:=$(CC) -isystem=$(INCLUDEDIR)

CFLAGS:=$(CFLAGS) -ffreestanding

export 


all:	myos.iso

install-headers:
	@for dir in $(PROJECTDIRS); do \
		$(MAKE) --no-print-directory -C $$dir install-headers; \
	done

install:
	@for dir in $(PROJECTDIRS); do \
		$(MAKE) --no-print-directory -C $$dir install; \
	done

myos.iso:	install-headers install
	@echo "Creating kernel ISO image..."
	@mkdir -p $(SYSROOT)$(BOOTDIR)/grub
	@echo -e 'menuentry "myos" {\n\tmultiboot $(BOOTDIR)/myos.bin\n}' > $(SYSROOT)$(BOOTDIR)/grub/grub.cfg
	@grub-mkrescue -o myos.iso $(SYSROOT)


start-kernel: myos.iso
	@qemu-system-i386 -kernel $(SYSROOT)$(BOOTDIR)/myos.bin

start: myos.iso
	@qemu-system-i386 -cdrom myos.iso


debug: CFLAGS:=$(CFLAGS) -ggdb3 -O0
debug: myos.iso
	@qemu-system-i386 -s -S -cdrom myos.iso &
	@sleep 0.5
	@gdb -q -ex "symbol-file $(SYSROOT)$(BOOTDIR)/myos.bin" -ex "target remote localhost:1234"

clean:
	@find . -type f \( -name '*.o' -o -name '*.bin' -o -name '*.d' -o -name '*.iso' -o -name '*.a' \) -exec rm {} \;
	@rm -rf $(SYSROOT)
