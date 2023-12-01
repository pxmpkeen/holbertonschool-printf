#include "main.h"
#include <limits.h>
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
		{'%', spec_percent},
		{'i', spec_int},
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
		else if (condition_spec && (format[i + 1] == 'i' || format[i + 1] == 'd'))
			specs[3].f(ap, &pc, &i);
		else
			c = format[i], write(1, &c, 1), i++, pc++;
	}
	va_end(ap);
	return (pc);
}
int main(void)
{
    int len;
    int len2;
    unsigned int ui;
    void *addr;

    len = _printf("Let's try to printf a simple sentence.\n");
    len2 = printf("Let's try to printf a simple sentence.\n");
    ui = (unsigned int)INT_MAX + 1024;
    addr = (void *)0x7ffe637541f0;
    _printf("Length:[%d, %i]\n", len, len);
    printf("Length:[%d, %i]\n", len2, len2);
    _printf("Negative:[%d]\n", -762534);
    printf("Negative:[%d]\n", -762534);
    _printf("Unsigned:[%u]\n", ui);
    printf("Unsigned:[%u]\n", ui);
    _printf("Unsigned octal:[%o]\n", ui);
    printf("Unsigned octal:[%o]\n", ui);
    _printf("Unsigned hexadecimal:[%x, %X]\n", ui, ui);
    printf("Unsigned hexadecimal:[%x, %X]\n", ui, ui);
    _printf("Character:[%c]\n", 'H');
    printf("Character:[%c]\n", 'H');
    _printf("String:[%s]\n", "I am a string !");
    printf("String:[%s]\n", "I am a string !");
    _printf("Address:[%p]\n", addr);
    printf("Address:[%p]\n", addr);
    len = _printf("Percent:[%%]\n");
    len2 = printf("Percent:[%%]\n");
    _printf("Len:[%d]\n", len);
    printf("Len:[%d]\n", len2);
    _printf("Unknown:[%r]\n");
    printf("Unknown:[%r]\n");
    return (0);
}
