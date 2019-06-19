#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../include/terminal.h"


static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

static uint16_t *term_buff = (uint16_t*) 0xB8000;
size_t term_row;
size_t term_column;
uint8_t term_color;

static inline size_t term_index(size_t x, size_t y)
{
	return y * VGA_WIDTH + x;
}

void term_setcolor(enum vga_color fg, enum vga_color bg)
{
	term_color = fg | bg << 4;
}

static void term_putentryat(char c, size_t x, size_t y)
{
	term_buff[term_index(x, y)] = c | term_color << 8;
}

void term_scroll(void)
{
	for (size_t row = 0; row < VGA_HEIGHT - 1; row++)
		for (size_t clmn = 0; clmn < VGA_WIDTH; clmn++)
			term_buff[term_index(clmn, row)] = term_buff[term_index(clmn, row + 1)];
	
	for (size_t clmn = 0; clmn < VGA_WIDTH; clmn++)
		term_buff[term_index(clmn, VGA_HEIGHT - 1)] = 0;
	
	term_row--;
}

void terminal_init(void)
{
	term_row = 0;
	term_column = 0;
	term_setcolor(VGA_LIGHT_GREY, VGA_BLACK);
	for (size_t y = 0; y < VGA_HEIGHT; y++)
		for (size_t x = 0; x < VGA_WIDTH; x++)
			term_putentryat(0, x, y);
}

static void term_putchar(char c)
{
	if (c == '\n') {
		term_column = 0;
		term_row++;
	} else {
		term_putentryat(c, term_column, term_row);
		if (++term_column == VGA_WIDTH) {
			term_column = 0;
			term_row++;
		}
	}


	if (term_row == VGA_HEIGHT)
		term_scroll();
}

void print(const char *data)
{
	while(*data)
		term_putchar(*data++);
}
