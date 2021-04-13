#include "./includes/minishell.h"

void	parsing(t_a *a)
{
	(void)a;
}

int		main(int ac, char **av, char **env)
{
	t_a a;

	a.ac = ac;
	a.av = av;
	a.env = env;
	
/*	int i = 1;
	while (env[++i])
		printf("%s\n", env[i]);*/

	while(1)
	{
		//ft_putstr_fd("On est chez nous:\n", 1);
		parsing(&a);
	}
	return (0);
}
