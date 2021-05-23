#include "../includes/minishell.h"

void	ft_affiche_controlesay(int useless)
{
	(void)useless;
	ft_putstr_fd("^C -Controle c avant d'avoir ecrit quoi que ce soit\n", 1);
	ft_title();
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
}

void	ft_ctrlc_in_buffer(int i)
{
	i = 0;
	ft_putstr_fd("-controle c, mais on a commence a ecrire\n", 1);
	ft_title();
	g_fantaisie = -30;
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
}

void	ft_exit_from_branch(int useless)
{
	(void)useless;
	g_fantaisie = 130;
	ft_putstr_fd("^C - ctrl c on tue une branche\n", 1);
}

void	ft_ctrl_antislash_in_function(int useless)
{
	(void)useless;
	g_fantaisie = 127;
	ft_putstr_fd("Quit: 3   - ctrl \\ dans une branche\n", 1);
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
