#include "../includes/minishell.h"

void	ft_affiche_controlesay(int useless)
{
	(void)useless;
	ft_putstr_fd("^C -VALIDER lE MESSAGE du controle c\n", 1);
	ft_title();
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
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
	ft_putstr_fd("^C -VALIDER CE MESSAGE SELON L OS\n", 1);
}

void	ft_nothing_to_do(int useless)
{
	(void)useless;
	//tputs(tgoto(tgetstr("sf", NULL), 0, 0), 1, ft_putchar);
}

void	ft_ctrlantislash(int useless)
{
	(void)useless;
	if (g_fantaisie == 0)
	{
		kill(g_fantaisie, SIGKILL);
		exit(0);
	}
	ft_putstr_fd("Quit (core dumped) - LE MESSAGE DU CTRL ANTISLASH DANS UNE FONCTION BLOQUANTE\n", 1);
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
}