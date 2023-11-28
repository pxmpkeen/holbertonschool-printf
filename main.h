#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>

int _printf(const char *format, ...);

/**
 * struct spec - defines specifications
 * @f: pointer to function
 * @type: type of va_arg
 */
typedef struct spec
{
	char type;
	void (*f)(va_list, int *count, int *i);
} spec_t;

#endif
