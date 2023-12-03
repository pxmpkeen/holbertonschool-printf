# DIY Printf (Holberton School)


Specifiers:
- `%c` - prints one single asciII character
- `%s` - prints the array of characters (string)
- `%d` - prints decimal number
- `%i` - prints the value of type integer
- `%%` - prints one percentage sign instead of two
## Table of Contents
- [Usage](#usage)
- [Example](#example)
- [Authors](#authors)

## Usage

Prototype of function:
```
int _printf(const char *format, ...);
```

To use our printf function you just need to include our head file "main.h":
```
#include "main.h"
```
To get man page of printf you can use `man` command in your terminal:
```
man _printf
```
Or just use this script:
```
./man_3_printf
```

## Examples

```
#include "main.h"

/**
 * main - entry point
 * Return: Always 0
 */
int main(void)
{
    char *str = "DIY";
    char c = 'N';
    int num = 98;

    _printf("Char is %c\n", c);
    _printf("Str is %s\n", str);
    _printf("Int is %d\n", num);

    return (0);
}
```
Output:
```
Char is N
Str is DIY
Int is 98

```

# Authors
Creators:
- Javid Jalilov [Pxmpkeen](https://github.com/pxmpkeen)
- Hasan Isgandarov [Hasan](https://github.com/hesen58)
- Father_of_C: Dennis Ritchie
