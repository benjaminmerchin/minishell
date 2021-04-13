#include "./includes/minishell.h"

int		main(int ac, char **av, char **env)
{
	t_a a;

	a.ac = ac;
	a.av = av;
	a.env = env;

	while(1)
	{
		ft_putstr_fd("Cristaline ", 1);
		ft_parsenv(&a);
		ft_putstr_fd("$ ", 1);
		ft_parsing(&a);
	}
	return (0);
}
