#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>


#define	LEN(x)	((sizeof (x))/(sizeof (x[0])))

char tohexchar(int n, bool upper)
{
	if (0 <= n && n < 10) {
		return n + 48;
	} else {
		return n + (upper ? 55 : 87);
	}
}


int printf(const char *format, ...)
{
	va_list parameters;
	va_start(parameters, format);
	
	size_t written = 0;
	char c;
	bool isInFormat = false;

	while ((c = *format++)) {
		if (isInFormat) {
			switch (c) {
			case '%':
				putchar('%');
				written++;
				break;
			case 'c':
				putchar(va_arg(parameters, int));
				written++;
				break;
			case 's':;
				const char *str = va_arg(parameters, const char*);
				while (*str) {
					putchar(*str++);
					written++;
				}
				break;
			case 'X':
			case 'x':;
				unsigned int n = va_arg(parameters, int);
				int nibbles[(sizeof (unsigned int)) * 2];

				for (size_t i = 0; i < LEN(nibbles); ++i) {
					nibbles[i] = ((n >> ((LEN(nibbles)-i-1) * 4)) & 0x0000000f);
				}

				for (size_t i = 0; i < LEN(nibbles); ++i)
					putchar(tohexchar(nibbles[i], c == 'X'));
				
				break;
			case 'n':;
				int *count = va_arg(parameters, int*);
				*count = written;
				break;
			}

			isInFormat = false;
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
