/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:21:54 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 23:21:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_home_and_replace_cd_with_home_path(t_a *a, int *i)
{
	t_list	*lst;

	(*i)--;
	lst = a->lst_env;
	while (lst)
	{
		if (ft_strncmp("HOME=", lst->content, 5) == 0)
		{
			free(a->raw[*i].str);
			a->raw[*i].str = ft_strdup(lst->content + 5);
			return ;
		}
		lst = lst->next;
	}
}

void	ft_cd(t_a *a, int *i)
{	
	int	ret;

	(*i)++;
	update_pwd(a, i);
	if (a->raw[*i].str == 0 || a->raw[*i].type == '|'
		|| a->raw[*i].type == ';')
		find_home_and_replace_cd_with_home_path(a, i);
	ret = chdir(a->raw[*i].str);
	if (ret < 0)
	{
		ft_putstr_fd("\033[031m", 1);
		ft_putstr_fd(MINISHELL_NAME, 1);
		ft_putstr_fd(": cd: ", 1);
		ft_putstr_fd(a->raw[*i].str, 1);
		ft_putstr_fd(": No such file or directory\033\n", 1);
		a->dollar_question = 127;
	}
	else
		a->dollar_question = 0;
	update_pwd(a, i);
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|'
		&& a->raw[*i].type != ';')
		(*i)++;
}
