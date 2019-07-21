#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "kernel/tty.h"


static uint16_t *term_buff = (uint16_t*) VGA_BUFFER;
size_t term_row;
size_t term_column;
uint8_t term_color;

static inline size_t term_index(size_t x, size_t y)
{
	return y * VGA_WIDTH + x;
}

void tty_setcolor(enum vga_color fg, enum vga_color bg)
{
	term_color = fg | bg << 4;
}

static void term_putentryat(char c, size_t x, size_t y)
{
	term_buff[term_index(x, y)] = c | term_color << 8;
}

void tty_scroll(void)
{
	for (size_t row = 0; row < VGA_HEIGHT - 1; row++)
		for (size_t clmn = 0; clmn < VGA_WIDTH; clmn++)
			term_buff[term_index(clmn, row)] = term_buff[term_index(clmn, row + 1)];
	
	for (size_t clmn = 0; clmn < VGA_WIDTH; clmn++)
		term_buff[term_index(clmn, VGA_HEIGHT - 1)] = 0;
	
	term_row--;
}

void tty_init(void)
{
	term_row = 0;
	term_column = 0;
	tty_setcolor(VGA_LIGHT_GREY, VGA_BLACK);
	for (size_t y = 0; y < VGA_HEIGHT; y++)
		for (size_t x = 0; x < VGA_WIDTH; x++)
			term_putentryat(0, x, y);
}

void tty_putchar(char c)
{
	switch (c) {
	case '\n':
		term_column = 0;
		term_row++;
		break;
	case '\r':
		term_column = 0;
		break;
	case '\v':
	case '\f':
		term_row++;
		break;
	default:
		term_putentryat(c, term_column, term_row);
		if (++term_column == VGA_WIDTH)
			tty_putchar('\n');
	}


	if (term_row == VGA_HEIGHT)
		tty_scroll();
}

size_t tty_print(const char *data)
{
	size_t len = 0;

	while(data[len])
		tty_putchar(data[len++]);

	return len;
}
