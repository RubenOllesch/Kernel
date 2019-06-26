LIBS=libk.a

LIBK_OBJS=stdio/puts.o


libk.a:	$(LIBK_OBJS)
	@$(AR) rcs $@ $(LIBK_OBJS)


install-headers:
	@mkdir -p $(SYSROOT)/$(INCLUDEDIR)
	@cp -R --preserve=timestamps include/. $(SYSROOT)/$(INCLUDEDIR)/.

install:	$(LIBS)
	@mkdir -p $(SYSROOT)/$(LIBDIR)
	@cp $(LIBS) $(SYSROOT)/$(LIBDIR)

%.o:	%.S
	@$(CC) -MD -c $< -o $@ $(CFLAGS)

%.o:	%.c
	@$(CC) -MD -c $< -o $@ $(CFLAGS) -std=gnu99