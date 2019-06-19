#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "terminal.h"

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void)
{
	terminal_init();


	term_setcolor(VGA_WHITE, VGA_BLACK);

	print("Hello, World!\n\n");


	for (size_t i; i < 16; ++i) {
		term_setcolor(i, VGA_BLACK);
		print("Colored Text on Black ");
		term_setcolor(VGA_BLACK, i);
		print("Black Text on Colored Background\n");
	}
}
