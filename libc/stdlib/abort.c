#include <stdio.h>
#ifdef __is_libk
#include <kernel/tty.h>
#endif

void abort(void)
{
#ifdef __is_libk
	tty_setcolor(VGA_BLACK, VGA_RED);
	printf("\nKernel panic");
	// TODO add core dump, etc..
#else
	// TODO user-space abort
#endif
}
