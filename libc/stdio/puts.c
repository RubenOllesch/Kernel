#include <kernel/tty.h>

int puts(const char *str)
{
	tty_print(str);
	tty_print("\n");
	return 0;
}
