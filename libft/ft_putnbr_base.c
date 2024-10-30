#include "libft.h"

void	ft_putnbr_base(int nbr, const char *base)
{
	if (nbr < 16)
		ft_putchar_fd(base[nbr], 1);
	else
	{
		ft_putnbr_base(nbr / 16, base);
		ft_putnbr_base(nbr % 16, base);
	}
}
