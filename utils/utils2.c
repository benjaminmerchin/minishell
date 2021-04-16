#include "../includes/minishell.h"

void	ft_init_struct(t_a *a)
{
	a->sep = SEPARATORS;
	a->nav = 0;
	a->nline = 0;
	a->backup_sep = a->sep;
	a->h = malloc(sizeof(char *) * 1000);
	a->term_type = getenv("TERM");
}

void	ft_putnbr_fd(int n, int fd)
{
	long nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putchar_fd(nbr % 10 + '0', fd);
	}
	else
		ft_putchar_fd(nbr + '0', fd);
}