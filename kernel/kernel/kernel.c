#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "kernel/tty.h"

void kernel_main(void)
{
	tty_init();


	tty_setcolor(VGA_WHITE, VGA_BLACK);

	puts("Hello, World!\n");


	for (size_t i = 0; i < 16; ++i) {
		tty_setcolor(i, VGA_BLACK);
		puts("Colored Text on Black ");
		tty_setcolor(VGA_BLACK, i);
		puts("Black Text on Colored Background");
	}
}
