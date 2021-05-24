/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_export_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:21:54 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 23:21:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_declare_print_export(t_a *a, int *i)
{
	int		j;
	t_list	*lst;

	(void)i;
	lst = a->lst_env;
	while (lst)
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (lst->content[j] != '=' && lst->content[j] != '\0')
		{
			ft_putchar_fd(lst->content[j], 1);
			j++;
		}
		if (lst->content[j] == '=')
		{
			ft_putchar_fd('=', 1);
			j++;
			ft_putchar_fd('"', 1);
			ft_putstr_fd(lst->content + j, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putstr_fd("\n", 1);
		lst = lst->next;
	}
}
