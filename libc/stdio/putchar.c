#include <kernel/tty.h>

int putchar(int c)
{
	tty_putchar(c);

	return c;
}