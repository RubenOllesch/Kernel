LIBS=libk.a

LIBK_OBJS=stdio/puts.o \
	stdio/putchar.o


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
