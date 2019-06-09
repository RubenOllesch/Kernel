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


	term_setcolor(VGA_LIGHT_GREY, VGA_BLACK);

	print("This is a nice day");

	print("\n\n");

	term_setcolor(VGA_BLACK, VGA_WHITE);

	print(" B L A C K \n");
	print("   O   N   \n");
	print(" W H I T E \n");


	term_setcolor(VGA_LIGHT_GREY, VGA_BLACK);

	print("\n\n");

	print("Have a nice day");
}
