#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>


int printf(const char *format, ...)
{
	va_list parameters;
	va_start(parameters, format);
	
	size_t written = 0;
	char c;
	bool isInFormat = false;

	while ((c= *format++)) {
		if (isInFormat) {
			switch (c) {
			case '%':
				isInFormat = false;
				putchar('%');
				written++;
				break;
			case 'c':
				isInFormat = false;
				putchar(va_arg(parameters, int));
				written++;
				break;
			case 's':
				isInFormat = false;
				const char *str = va_arg(parameters, const char*);
				while (*str) {
					putchar(*str++);
					written++;
				}
				break;
			case 'n':
				isInFormat = false;
				int *count = va_arg(parameters, int*);
				*count = written;
				break;
			}
		} else {
			if (c == '%') {
				isInFormat = true;
				continue;
			}

			putchar(c);
			written++;
		}
	}

	va_end(parameters);

	return written;
}