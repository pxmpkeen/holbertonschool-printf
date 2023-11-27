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
	int condition;
	int i = 0, pc = 0, sl = 0;
	char endl = 10;
	char character, *string;


	va_start(ap, format);
	if (!format)
		return (0);
	while (format[i])
	{
		condition = (format[i] == '%');
		if (condition && format[i + 1] == 'c')
		{
			character = (char)va_arg(ap, int);
			write(1, &character, 1), i += 2, pc++;
		}
		else if (condition && format[i + 1] == 's')
		{
			string = va_arg(ap, char *);
			while (string[sl])
				sl++;
			write(1, string, sl);
			i += 2, pc += sl, sl = 0;
		}
		else if (condition && format[i + 1] == '%')
		{
			character = '%';
			write(1, &character, 1), i += 2, pc++;
		}
		else
		{
			character = format[i];
			write(1, &character, 1), i++, pc++;
		}
	}
	write(1, &endl, 1);
	va_end(ap);
	return (pc);
}
