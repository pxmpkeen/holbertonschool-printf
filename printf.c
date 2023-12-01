#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
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
 * spec_int - something usefull
 * @ap: va_list
 * @pc: printed counter
 * @i: iterator
 */
void spec_int(va_list ap, int *pc, int *i)
{
	int j = 0, mod;
	char c[11], min = '-', zero = '0', cj;
	unsigned int num;
	int n = va_arg(ap, int);

	if (n < 0)
	{
		num = -1 * n;
		(*pc) += write(1, &min, 1);
	}
	else
		num = n;
	if (num == 0)
		(*pc) += write(1, &zero, 1);
	while (num > 0)
	{
		mod = num % 10;
		c[j] = mod + '0';
		num /= 10;
		j++;
	}
	j--;
	while (j >= 0)
	{
		cj = c[j];
		(*pc) += write(1, &cj, 1);
		j--;
	}
	*i += 2;
}
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
 * _printf - handmade printf
 * @format: input string
 * Return: number of chars
 */
int _printf(const char *format, ...)
{
	va_list ap;
	char c;
	int condition_spec, i = 0, pc = 0, l;
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
