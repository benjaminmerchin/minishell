#include "../includes/minishell.h"

void	ft_parsenv(t_a *a)
{
	int i;

	i = -1;
	while (a->env[++i])
	{
		if (ft_strncmp(a->env[i], "PWD=", 4) == 0)
		{
			ft_putstr_fd(a->env[i] + 4, 1);
			break ;
		}
	}
}

void	ft_parsing(t_a *a)
{

	get_next_line(0, &a->line);
/*	if (a->line[0] == 'a')
		ft_putstr_fd(" On capture bien\n", 1);*/
}
