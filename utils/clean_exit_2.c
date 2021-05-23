/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:00:55 by user42            #+#    #+#             */
/*   Updated: 2021/03/18 19:04:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_a *a)
{
	if (!a->raw[a->i + 1].type)
		ft_exit_clean(a, "");
	if (a->len_raw > a->i + 2 && a->raw[a->i + 2].type != ';')
	{
		ft_putstr_fd("exit\033[031m\n", 1);
		ft_putstr_fd(MINISHELL_NAME, 1);
		ft_putstr_fd(": exit: too many arguments\033\n", 1);
		while (a->i < a->len_raw)
			a->i++;
		return ;
	}
	ft_manage_exit_argument(a);
}

void	set_backup_and_exit(t_a *a, char *str)
{
	a->line = a->backup;
	ft_exit_clean(a, str);
}
