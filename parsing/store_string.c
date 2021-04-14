#include "../includes/minishell.h"

void 			ft_store_string(t_a *a)
{
	int i;
	//write(1, "@", 1);
	//ft_putstr_fd(a->line, 1);
	//while ()
	ft_split_sh(a);
	i = 0;
	while (a->raw[i].str)
	{
		ft_putchar_fd('[', 1);
		ft_putchar_fd(a->raw[i].type, 1);
		ft_putchar_fd(']', 1);
//		ft_putnbr_fd(a->raw[i].type, 1);
		ft_putchar_fd(' ', 1);
		ft_putchar_fd('[', 1);
		ft_putstr_fd(a->raw[i].str, 1);
		ft_putchar_fd(']', 1);
		write(1, "\n", 1);
		i++;
	}
}
