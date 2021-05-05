#include "../includes/minishell.h"

void	ft_stayinalive(int useless)
{
	(void)useless;

	if (g_fantaisie == 0)
	{
		ft_putstr_fd("^C\n", 1);
		ft_title();
		tputs(tgetstr("sc", NULL), 1, ft_putchar);
	}
	g_fantaisie = 130;
	exit(0);
}

void	ft_ctrlantislash(int useless)
{
	(void)useless;
	//To update when pipes will be properly done
	/*
	if (g_fantaisie < 0 || g_fantaisie > 1)
		ft_putstr_fd("Quit (core dumped)\n", 1);
	g_fantaisie = 0;
	*/
}