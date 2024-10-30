#include "libft.h"

int	ft_countdigits(int n)
{
	int	digits;

	digits = 0;
	if (n < 0)
	{
		n *= -1;
		++digits;
	}
	if (n == 0)
		digits = 1;
	while (n)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}
