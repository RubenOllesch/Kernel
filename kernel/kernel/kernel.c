#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "kernel/tty.h"

const char *samplesource =
	"size_t tty_print(const char *data)\n"
	"{\n"
	"\tsize_t len = 0;\n"
	"\n"
	"\twhile(data[len])\n"
	"\t\ttty_putchar(data[len++]);\n"
	"\n"
	"\treturn len;\n"
	"}\n"
;


void kernel_main(void)
{
	tty_init();


	tty_setcolor(VGA_WHITE, VGA_BLACK);

	puts("Hello, World!");

	for (size_t i = 0; i < 8; ++i) {
		tty_setcolor(i, VGA_BLACK);
		printf("Colored Text on Black\t");
		tty_setcolor(VGA_BLACK, i);
		printf("Black Text on Colored Background\t\n");
	}

	putchar('\n');

	tty_setcolor(VGA_LIGHT_GREY, VGA_BLACK);

	puts(samplesource);
}
