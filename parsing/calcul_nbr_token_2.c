/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_nbr_token_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:21:54 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 23:21:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	calcul_k_6(t_a *a, int *i, int *counter)
{
	(a->line)++;
	*counter = 0;
	while (a->line[*counter] != '\'' && a->line[*counter] != '\0')
		(*counter)++;
	if (a->line[*counter] == '\0')
		set_backup_and_exit(a, "Error\nEnding quote missing\n");
	while (*counter > 0)
	{
		(*i)++;
		(*counter)--;
		(a->line)++;
	}
	*i = 0;
}

void	calcul_k_5(t_a *a, int *i, int *counter)
{
	if (a->line[*i] == '"')
	{
		(a->line)++;
		*counter = 0;
		while (a->line[*counter] != '"' && a->line[*counter] != '\0')
			(*counter)++;
		if (a->line[*counter] == '\0')
			set_backup_and_exit(a, "Error\nEnding quote missing\n");
		while (*counter > 0)
		{
			(*i)++;
			(*counter)--;
			(a->line)++;
		}
		*i = 0;
	}
	else
		calcul_k_6(a, i, counter);
	(a->line)++;
}

void	calcul_k_4(t_a *a)
{
	(a->line)++;
	(a->line)++;
}
