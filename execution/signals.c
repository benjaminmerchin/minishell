#include "../includes/minishell.h"

void	ft_voidtitle(void)
{
	char	pwdname[1024];

	ft_putstr_fd(MINISHELL_NAME, 1);
	ft_putstr_fd(" ", 1);
	if (getcwd(pwdname, sizeof(pwdname)) == NULL)
		return ;
	ft_putstr_fd(pwdname, 1);
	ft_putstr_fd("> ", 1);
}

void	ft_update_exitcode(t_a *a)
{
	//fonction à construire pour récupérer les $?
	(void)a;
}

void	ft_stayinalive(int useless)
{
	(void)useless;
	ft_putstr_fd("^C\n", 1);
	ft_voidtitle();
	tputs(tgetstr("sc", NULL), 1, ft_putchar);
}