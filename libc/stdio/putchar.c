#ifdef __is_libk
#include <kernel/tty.h>
#endif

int putchar(int c)
{
#ifdef __is_libk
	tty_putchar(c);

	return c;
#else
	// TODO: Hosted libc implementation
#endif
}