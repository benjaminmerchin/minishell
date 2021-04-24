/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:21:54 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 23:21:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parsenv(t_a *a)
{
	t_list *lst;

	lst = a->lst_env;
	while (lst)
	{
		if (ft_strncmp("PWD=", lst->content, 4) == 0)
		{
			ft_putstr_fd(lst->content + 4, 1);
			a->len_head += ft_strlen(lst->content);
			return ;
		}
		lst = lst->next;
	}
}

void	ft_parsing(t_a *a)
{
	if (DEBUG)
		a->line = LINE_CONTENT;
	else
		get_next_line(0, &a->line);
}
