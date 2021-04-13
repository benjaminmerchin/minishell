#include "../includes/minishell.h"

void	ft_parsing(t_a *a)
{

	while(get_next_line(0, &a->line))
		;
	//ft_putstr_fd(a->line, 1);
	if (a->line[0] == 'a')
		ft_putstr_fd("/nOn capture bien\n", 1);
}
