#include "libft.h"

char    *ft_strndup(const char *s, size_t n)
{
    char *dup;

    dup = malloc(n + 1);
    if (dup)
    {
        ft_strncpy(dup, s, n);
        dup[n] = '\0';
    }
    return dup;
}