#include "main.h"
#include <stdarg.h>
#include <unistd.h>
/**
 * _printf - handmade printf
 * @format: input string
 * Return: number of chars
 */
int _printf(const char *format, ...)
{
	va_list ap;
	int condition_p, condition_b, i = 0, pc = 0, sl = 0;
	char endl = 10, c, *s;

	va_start(ap, format);
	if (!format)
		return (0);
	while (format[i])
	{
		condition_b = (format[i] == 92)
		condition_p = (format[i] == '%');
		if (condition_p && format[i + 1] == 'c')
		{
			c = (char)va_arg(ap, int);
			write(1, &c, 1), i += 2, pc++;
		}
		else if (condition_p && format[i + 1] == 's')
		{
			s = va_arg(ap, char *);
			while (s[sl])
				sl++;
			write(1, s, sl), i += 2, pc += sl, sl = 0;
		}
		else if (condition_p && format[i + 1] == '%')
			c = '%', write(1, &c, 1), i += 2, pc++;
		else if (condition_b && format[i + 1] == 'n')
			write(1, &endl, 1), i += 2, pc++;
		else
			c = format[i], write(1, &c, 1), i++, pc++;
	}
	va_end(ap);
	return (pc);
}
