#include "../includes/minishell.h"

void	ft_init_struct(t_a *a)
{
	a->sep = SEPARATORS;
	a->nav = 0;
	a->nline = 0;
	a->backup_sep = a->sep;
	a->h = malloc(sizeof(char *) * 1000);
//	a->term_type = getenv("TERM");
	a->fd = 0;
	a->line = NULL;
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

void	ft_print_string(t_a *a)
{
	int i;

	i = 0;
	ft_putchar_fd('\n', 1);
	while (a->raw[i].str && !a->nav)
	{
		ft_putchar_fd('[', 1);
		ft_putchar_fd(a->raw[i].type, 1);
		ft_putchar_fd(']', 1);
//		ft_putnbr_fd(ft_strlen(a->sep), 1);
		ft_putchar_fd(' ', 1);
		ft_putchar_fd('[', 1);
		ft_putstr_fd(a->raw[i].str, 1);
		ft_putchar_fd(']', 1);
		write(1, "\n", 1);
		i++;
	}
}
