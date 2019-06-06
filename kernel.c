#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

/* Hardware text mode color constants. */
enum vga_color {
	VGA_BLACK = 0,
	VGA_BLUE = 1,
	VGA_GREEN = 2,
	VGA_CYAN = 3,
	VGA_RED = 4,
	VGA_MAGENTA = 5,
	VGA_BROWN = 6,
	VGA_LIGHT_GREY = 7,
	VGA_DARK_GREY = 8,
	VGA_LIGHT_BLUE = 9,
	VGA_LIGHT_GREEN = 10,
	VGA_LIGHT_CYAN = 11,
	VGA_LIGHT_RED = 12,
	VGA_LIGHT_MAGENTA = 13,
	VGA_LIGHT_BROWN = 14,
	VGA_WHITE = 15,
};

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static uint16_t* term_buff = (uint16_t*) 0xB8000;
size_t term_row;
size_t term_column;
uint8_t terminal_color;

static inline size_t term_index(size_t x, size_t y)
{
	return y * VGA_WIDTH + x;
}

void terminal_setcolor(enum vga_color fg, enum vga_color bg)
{
	terminal_color = fg | bg << 4;
}

void terminal_putentryat(char c, size_t x, size_t y)
{
	term_buff[term_index(x, y)] = c | terminal_color << 8;
}

void terminal_scroll(void)
{
	for (size_t row = 0; row < VGA_HEIGHT - 1; row++) {
		for (size_t clmn = 0; clmn < VGA_WIDTH; clmn++) {
			term_buff[term_index(clmn, row)] = term_buff[term_index(clmn, row + 1)];
		}
	}
	
	for (size_t clmn = 0; clmn < VGA_WIDTH; clmn++)
		term_buff[term_index(clmn, VGA_HEIGHT - 1)] = 0;
	
	term_row--;
}

void terminal_initialize(void)
{
	term_row = 0;
	term_column = 0;
	terminal_setcolor(VGA_LIGHT_GREY, VGA_BLACK);
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			terminal_putentryat(0, x, y);
		}
	}
}

void terminal_putchar(char c)
{
	if (c == '\n') {
		term_column = 0;
		term_row++;
	} else {
		terminal_putentryat(c, term_column, term_row);
		if (++term_column == VGA_WIDTH) {
			term_column = 0;
			term_row++;
		}
	}


	if (term_row == VGA_HEIGHT)
		terminal_scroll();
}

void terminal_print(const char* data)
{
	while(*data) {
		terminal_putchar(*data++);
	}
}

void kernel_main(void)
{
	/* Initialize terminal interface */
	terminal_initialize();

	terminal_print("Hello, kernel World!\n");
}
