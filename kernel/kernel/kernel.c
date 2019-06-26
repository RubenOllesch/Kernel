#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "kernel/tty.h"

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
