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
