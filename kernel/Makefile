LIBS?=
LIBS:=-lk -nostdlib -lgcc


ARCHDIR=arch

OBJ=kernel/kernel.o \
	$(ARCHDIR)/boot.o \
	$(ARCHDIR)/tty.o


install-headers:
	@echo "Installing kernel headers..."
	@mkdir -p $(SYSROOT)$(INCLUDEDIR)
	@cp -R --preserve=timestamps include/. $(SYSROOT)$(INCLUDEDIR)/.

install:	myos.bin
	@echo "Installing kernel..."
	@mkdir -p $(SYSROOT)$(BOOTDIR)
	@cp myos.bin $(SYSROOT)$(BOOTDIR)

myos.bin:	$(OBJ) $(ARCHDIR)/linker.ld
	@echo "Building kernel..."
	@$(CC) -T $(ARCHDIR)/linker.ld -o myos.bin -ffreestanding -O2 $(OBJ) $(LIBS)
	@grub-file --is-x86-multiboot myos.bin

%.o:	%.S
	@$(CC) -MD -c $< -o $@ $(CFLAGS)

%.o:	%.c
	@$(CC) -MD -c $< -o $@ $(CFLAGS) -std=gnu99
