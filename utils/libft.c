#include "../includes/minishell.h"

void	ft_putnbr(int n)
{
	long nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10);
		ft_putchar(nbr % 10 + '0');
	}
	else
		ft_putchar(nbr + '0');
}

void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

int	ft_isprint(int c)
{
	return (c >= ' ' && c <= '~');
}
