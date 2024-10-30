#include "../includes/ft_printf.h"

void	putnbr_unsigned(unsigned int nb, int *pcount)
{
	if (nb >= 10)
	{
		putnbr_unsigned(nb / 10, pcount);
		putnbr_unsigned(nb % 10, pcount);
	}
	else
	{
		ft_putchar_fd(nb + '0', 1);
		(*pcount)++;
	}
}

void	putnbr_base_hex(unsigned int nbr, const char *base, int *pcount)
{
	int	destlen;

	destlen = ft_strlen(base);
	if (nbr < (unsigned int)destlen)
	{
		write(1, &base[nbr], 1);
		(*pcount)++;
	}
	else
	{
		putnbr_base_hex(nbr / (unsigned int)destlen, base, pcount);
		putnbr_base_hex(nbr % (unsigned int)destlen, base, pcount);
	}
}

void	putnbr_base_p(unsigned long long nbr, const char *base, int *pcount)
{
	int	destlen;

	destlen = ft_strlen(base);
	if (nbr < (unsigned long long)destlen)
	{
		write(1, &base[nbr], 1);
		(*pcount)++;
	}
	else
	{
		putnbr_base_p(nbr / (unsigned long long)destlen, base, pcount);
		putnbr_base_p(nbr % (unsigned long long)destlen, base, pcount);
	}
}
