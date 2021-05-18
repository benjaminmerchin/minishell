#include "../includes/minishell.h"

void	ft_affiche_controlesay(int useless)
{
	(void)useless;
	ft_putstr_fd("^C\n", 1);
	ft_title();
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
	//kill(g_fantaisie, SIGKILL);
	//exit(0);
}

void	ft_exit_from_branch(int useless)
{
	(void)useless;
	if (g_fantaisie == 0)
	{
		ft_putstr_fd("^C\n", 1);
		g_fantaisie = 130;
		exit(0);
	}
	ft_putstr_fd("UN MESSAGE D'ERREUR QUI DEPEND DE L'OS\n", 1);
}

void	ft_nothing_to_do(int useless)
{
	(void)useless;
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