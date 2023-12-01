#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
/**
 * spec_placeholder - something usefull
 * @ap: va_list
 * @pc: printed counter
 * @i: iterator
 */
void spec_placeholder(va_list ap, int *pc, int *i)
{
	char c = (char)va_arg(ap, int);

	(*pc) += write(1, &c, 1), *i += 2;
}
/**
 * formatter - formates char to another one
 * @c: initial char
 * Return: changed char
 */
char formatter(char c)
{
	char ch;

	switch (c)
	{
		case 32:
			ch = 97;
			break;
		case 35:
			ch = 101;
			break;
		case 37:
			ch = 102;
			break;
		case 43:
			ch = 103;
			break;
		case 46:
			ch = 106;
			break;
		case 82:
			ch = 109;
			break;
		case 83:
			ch = 110;
			break;
		case 88:
			ch = 113;
			break;
		case 48:
			ch = 116;
			break;
		case 120:
			ch = 118;
			break;
		default:
			ch = c;
	}
	return (ch);
}
/**
 * specs_func - specs function
 *
 * Return: spec_t
 */
spec_t *specs_func()
{
	spec_t specs[] = {
		{' ', spec_placeholder},
		{'b', spec_placeholder},
		{'c', spec_char},
		{'d', spec_int},
		{'#', spec_placeholder},
		{'%', spec_percent},
		{'+', spec_placeholder},
		{'h', spec_placeholder},
		{'i', spec_int},
		{'.', spec_placeholder},
		{'-', spec_placeholder},
		{'l', spec_placeholder},
		{'R', spec_placeholder},
		{'S', spec_placeholder},
		{'o', spec_placeholder},
		{'p', spec_placeholder},
		{'X', spec_placeholder},
		{'r', spec_placeholder},
		{'s', spec_string},
		{'0', spec_placeholder},
		{'u', spec_placeholder},
		{'x', spec_placeholder},
	};

	return (specs);
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
	int condition_spec, i = 0, pc = 0, l;
	spec_t *specs = specs_func();

	if (!format)
		exit(98);
	if (*format == '%' && *(format + 1) == 0)
		exit(98);
	va_start(ap, format);
	while (format[i])
	{
		condition_spec = (format[i] == '%');
		l = formatter(format[i + 1]);
		if (condition_spec && l >= 97 && l <= 118)
			specs[l - 97].f(ap, &pc, &i);
		else
			c = format[i], write(1, &c, 1), i++, pc++;
	}
	va_end(ap);
	return (pc);
}
