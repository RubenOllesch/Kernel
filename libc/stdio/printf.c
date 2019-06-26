#ifdef __is_libk
#include <kernel/tty.h>
#endif

int printf(const char *format, ...)
{
#ifdef __is_libk
	return (int) tty_print(format);
#else
	// TODO: Hosted libc implementation
#endif
}