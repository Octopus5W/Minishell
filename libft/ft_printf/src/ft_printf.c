#include "../includes/ft_printf.h"

static void format(va_list arg, char c, int *pcount)
{
    if (c == '%')
    {
        write(1, "%", 1);
        ++(*pcount);
    }
    else if (c == 'c')
    {
        ft_putchar_fd(va_arg(arg, int), 1); 
        ++(*pcount);
    }
    else if (c == 's')
        string(arg, pcount);
    else if (c == 'p')
       pointer(arg, pcount);
    else if (c == 'd' || c == 'i')
        integer(arg, pcount);
    else if (c == 'u')
        unsigned_int(arg, pcount);
    else if (c == 'x'|| c == 'X')
        hexadecimal(arg, pcount, c);
}

int ft_printf(const char *s, ...)
{
    va_list arg;
    int     pcount;

    va_start(arg, s);
    pcount = 0;
    while (*s)
    {
        if (*s != '%')
        {
            ft_putchar_fd(*s, 1); 
            ++pcount;
        }
        else
            format(arg, *++s, &pcount);
        ++s;
    }
    va_end(arg);
    return (pcount);
}
