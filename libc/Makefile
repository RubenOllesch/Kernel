LIBS=libk.a

FREEOBJS=stdio/puts.o \
	stdio/putchar.o \
	stdio/printf.o

HOSTEDOBJS=


# libk is the libc implemenation for use in the kernel
LIBK_OBJS=$(FREEOBJS:.o=.libk.o)
LIBK_FLAGS=-D__is_libk

libk.a:	$(LIBK_OBJS)
	@echo "Building libk.a..."
	@$(AR) rcs $@ $(LIBK_OBJS)


install-headers:
	@echo "Installing libc headers..."
	@mkdir -p $(SYSROOT)/$(INCLUDEDIR)
	@cp -R --preserve=timestamps include/. $(SYSROOT)/$(INCLUDEDIR)/.

install:	$(LIBS)
	@echo "Installing libc..."
	@mkdir -p $(SYSROOT)/$(LIBDIR)
	@cp $(LIBS) $(SYSROOT)/$(LIBDIR)

%.o:	%.S
	@$(CC) -MD -c $< -o $@ $(CFLAGS)

%.o:	%.c
	@$(CC) -MD -c $< -o $@ $(CFLAGS) -std=gnu99

%.libk.o:	%.S
	@$(CC) -MD -c $< -o $@ $(CFLAGS) $(LIBK_FLAGS)

%.libk.o:	%.c
	@$(CC) -MD -c $< -o $@ $(CFLAGS) $(LIBK_FLAGS) -std=gnu99