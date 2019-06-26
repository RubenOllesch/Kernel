#include <kernel/tty.h>

int printf(const char *format, ...)
{
	return (int) tty_print(format);
}