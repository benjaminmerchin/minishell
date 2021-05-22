#include "../includes/minishell.h"

void	ft_affiche_controlesay(int useless)
{
	(void)useless;
	ft_putstr_fd("^C -VALIDER lE MESSAGE du controle c\n", 1);
	ft_title();
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
}

void	ft_ctrlc_in_buffer(int i)
{
	i = 0;
	ft_putstr_fd("-controle c avec une chaine de caracteres\n", 1);
	ft_title();
	g_fantaisie = -30;
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
}

void	ft_exit_from_branch(int useless)
{
	(void)useless;
	if (g_fantaisie == 0)
	{
		ft_putstr_fd("On quitte la branche\n", 1);
		//g_fantaisie = 130;
		exit(130);
	}
	//ft_putstr_fd("^C - VALIDER CE MESSAGE SELON L OS\n", 1);
}

void	ft_nothing_to_do(int useless)
{
	(void)useless;
}

void	ft_jump_line(int useless)
{
	(void)useless;
	ft_putstr_fd("\n", 1);
}
