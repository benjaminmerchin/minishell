#include "../includes/minishell.h"

void	ft_init_struct(t_a *a)
{
	int	i;

	i = -1;
	a->sep = SEPARATORS;
	a->nav = 0;
	a->nline = 0;
	if (TERMCAPS)
	{	a->h = malloc(sizeof(char *) * 1000);
		if (!a->h)
			exit(0);
		while (i++ < 999)
			a->h[i] = NULL;
	}
	a->len_head = ft_strlen(MINISHELL_NAME) + 1;
	a->fd = 0;
	a->line = NULL;
	a->v_fd = -1;
	a->dollar_question = 0;
	g_fantaisie = -1;
	a->fd_input = 0;
	a->fd_output = 1;
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
	//ft_putchar_fd('\n', 1);
	if (PRINT_TOKENS == 0)
		return ;
	while (a->raw[i].str)
	{
		ft_putchar_fd('[', 1);
		ft_putchar_fd(a->raw[i].type, 1);
		ft_putchar_fd(']', 1);
		ft_putchar_fd(' ', 1);
		ft_putchar_fd('[', 1);
		if (a->raw[i].space_before == 1)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(a->raw[i].str, 1);
		ft_putchar_fd(']', 1);
		write(1, "\n", 1);
		i++;
	}
}

int	ft_atoi(const char *nptr)
{
	long long int		i;
	long long int		r;
	long long int		s;

	i = 0;
	r = 0;
	s = 1;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-')
	{
		s = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0')
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
			r = r * 10 + nptr[i] - '0';
		else
			break ;
		i++;
	}
	return (s * r);
}