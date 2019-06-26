#ifdef __is_libk
#include <kernel/tty.h>
#endif

int puts(const char *str)
{
#ifdef __is_libk
	tty_print(str);
	tty_print("\n");
	return 0;
#else
	// TODO: Hosted libc implementation
#endif
}
