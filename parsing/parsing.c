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
	

}


/*
	if (ft_strncmp(a->line, "^[[A", 4) == 0 && a->nav <= a->nline)
	{
		ft_putstr_fd("\n****on a chopé fleche haut****\n", 1);
		a->nav++;
		ft_nav(a);
	}
	else if( ft_strncmp(a->line, "^[[B", 4) == 0 && a->nav > 0)
	{
		ft_putstr_fd("\n****on a chopé fleche bas****\n", 1);
		a->nav--;
		ft_nav(a);
	}
	else
		ft_save_hist(a, a->line);
*/