/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:21:54 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 23:21:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_me_if_i_exist(t_a *a, int *i, int ret)
{
	t_list	*lst;
	t_list	*lst_before;
	int		v_bool_fist_element;

	ret--;
	lst = a->lst_env;
	v_bool_fist_element = 1;
	while (lst)
	{
		if (ft_strncmp(a->raw[*i].str, lst->content, ret) == 0)
		{
			free(lst->content);
			if (v_bool_fist_element == 1)
				a->lst_env = a->lst_env->next;
			else
				lst_before->next = lst->next;
			return ;
		}
		v_bool_fist_element = 0;
		lst_before = lst;
		lst = lst->next;
	}
}

void	ft_unset(t_a *a, int *i)
{
	int	ret;

	(*i)++;
	a->dollar_question = 0;
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|'
		&& a->raw[*i].type != ';')
	{
		ret = ft_verification_content(a->raw[*i].str, a, i);
		if (ret > 0)
			remove_me_if_i_exist(a, i, ret);
		(*i)++;
	}
}
