#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/**
 * spec_char - Something usefull
 * @ap: va_list
 * @pc: printed counter
 * @i: iterator
 * Return: Something more usefull
 */
void spec_char(va_list ap, int *pc, int *i)
{
	char c = (char)va_arg(ap, int);

	(*pc) += write(1, &c, 1), *i += 2;
}
/**
 * spec_percent - Something usefull
 * @ap: va_list
 * @pc: printed counter
 * @i: iterator
 * Return: Something more usefull
 */
void spec_percent(va_list ap, int *pc, int *i)
{
	char c = '%';
	(void)ap;

	(*pc) += write(1, &c, 1), *i += 2;
}
/**
 * spec_string - something usefull
 * @ap: va_list
 * @pc: printed counter
 * @i: iterator
 */
void spec_string(va_list ap, int *pc, int *i)
{
	int sl = 0;
	char *s = va_arg(ap, char *);

	if (!s)
		s = "(null)";

	while (s[sl])
		sl++;
	(*pc) += write(1, s, sl), *i += 2;
}
/**
 * _printf - handmade printf
 * @format: input string
 * Return: number of chars
 */
int _printf(const char *format, ...)
{
	va_list ap;
	char c;
	int condition_spec, i = 0, pc = 0;
	spec_t specs[] = {
		{'c', spec_char},
		{'s', spec_string},
		{'%', spec_percent}
	};

	if (!format)
		exit(98);
	if (*format == '%' && *(format + 1) == 0)
		exit(98);

	va_start(ap, format);
	while (format[i])
	{
		condition_spec = (format[i] == '%');
		if (condition_spec && format[i + 1] == 'c')
			specs[0].f(ap, &pc, &i);
		else if (condition_spec && format[i + 1] == 's')
			specs[1].f(ap, &pc, &i);
		else if (condition_spec && format[i + 1] == '%')
			specs[2].f(ap, &pc, &i);
		else
			c = format[i], write(1, &c, 1), i++, pc++;
	}
	va_end(ap);
	return (pc);
}
