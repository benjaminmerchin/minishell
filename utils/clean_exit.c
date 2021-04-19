/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:00:55 by user42            #+#    #+#             */
/*   Updated: 2021/03/18 19:04:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cleanstruct(t_a *a)
{
	int		i;

	i = -1;
	while (a->raw[++i].str)
		free(a->raw[i].str);
	free (a->raw);
	if (a->line)
		free(a->line);
	a->line = NULL;
	a->sep = SEPARATORS;
}

void	ft_cleantermcaps(t_a *a)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &a->trms);
}

void	ft_exit_clean(t_a *a, char *str)
{
	ft_putstr_fd(str, 2);
	ft_cleanstruct(a);
	//ft_putnbr(ft_lstsize(a->lst_env));
	ft_lstclear(&(a->lst_env)); // free env list
	if (TERMCAPS)
		ft_cleantermcaps(a); //clairement ça ne clean pas encore tout
	//free everything
	exit (0);
}

void	set_backup_and_exit(t_a *a, char *str)
{
	a->line = a->backup;
	ft_exit_clean(a, str);
}
