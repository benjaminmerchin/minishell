#include "../includes/minishell.h"

void	ft_parsenv(t_a *a)
{
	t_list *lst;

	lst = a->lst_env;
	while (lst)
	{
		if  (ft_strncmp("PWD=", lst->content, 4) == 0)
		{
			ft_putstr_fd(lst->content + 4, 1); //attention fd = 1
			return ;
		}
		lst = lst->next;
	}
}

void	ft_parsing(t_a *a)
{
	get_next_line(0, &a->line);
}
