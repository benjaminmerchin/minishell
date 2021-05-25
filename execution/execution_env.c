/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:21:54 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 23:21:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	content_have_value(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_env_2(t_a *a, int *i)
{
	a->dollar_question = 1;
	ft_putstr_fd("env: ", 1);
	ft_putstr_fd(a->raw[*i + 1].str, 1);
	ft_putstr_fd(": No such file or \n", 1);
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' \
	&& a->raw[*i].type != ';')
		(*i)++;
}

void	ft_env(t_a *a, int *i)
{
	t_list	*lst;

	a->dollar_question = 0;
	lst = a->lst_env;
	update_pwd(a, i);
	while (a->raw[*i + 1].str && ft_strncmp(a->raw[*i].str, \
	a->raw[*i + 1].str, 10) == 0 && ft_strlen(a->raw[*i + 1].str) == 3)
		(*i)++;
	if (!(a->raw[*i + 1].str == 0 || a->raw[*i + 1].type == '|' \
	|| a->raw[*i + 1].type == ';'))
	{
		ft_env_2(a, i);
		return ;
	}
	while (lst)
	{
		if (content_have_value(lst->content))
		{
			ft_putstr_fd(lst->content, 1);
			ft_putstr_fd("\n", 1);
		}
		lst = lst->next;
	}
	(*i)++;
}
