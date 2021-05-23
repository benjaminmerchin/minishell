/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:21:54 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 23:21:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_split_and_backup(t_a *a, int *i, int *k)
{
	int l;

	l = 0;
	while (a->line[l])
		l++;
	if (l > 0 && a->line[l - 1] == ' ')
	{
		a->line[l - 1] = '\0';
		init_split_and_backup(a, i, k);
	}
	*i = 0;
	*k = 0;
	a->backup = a->line;
	a->raw[*k].str = 0;
	a->raw[*k].type = 0;
	a->raw[*k].space_before = 0;
}

void	skip_spaces(t_a *a, int *i, int *k)
{
	a->raw[*k].space_before = 0;
	if (a->line[*i] == ' ')
	{
		a->raw[*k].space_before = 1;
		while (is_sep(a->line[*i + 1], a) && a->line[*i] == ' ')
			(a->line)++;
	}
}

void	manage_text(t_a *a, int *i, int *k, int *counter)
{
	a->raw[*k].type = ' ';
	if (a->line[0] == ' ')
	{
		(a->line)++;
		a->raw[*k].space_before = 1;
	}
	if (a->line[0] == '\0')
		return ;
	*counter = 0;
	while (!is_sep(a->line[*counter], a) && a->line[*counter] != '\0')
		(*counter)++;
	a->raw[*k].str = malloc(sizeof(char) * (*counter + 1));
	if (!a->raw[*k].str)
		set_backup_and_exit(a, "Error\nMalloc Failed\n");
	while (*counter > 0)
	{
		a->raw[*k].str[*i] = a->line[0];
		(*i)++;
		(*counter)--;
		(a->line)++;
	}
	a->raw[*k].str[*i] = 0;
	*i = 0;
}

void	manage_double_greater_than_sign(t_a *a, int *k)
{
	a->raw[*k].type = '#';
	a->raw[*k].str = malloc(sizeof(char) * 3);
	if (!a->raw[*k].str)
		set_backup_and_exit(a, "Error\nMalloc Failed\n");
	a->raw[*k].str[0] = '>';
	a->raw[*k].str[1] = '>';
	a->raw[*k].str[2] = 0;
	(a->line)++;
	(a->line)++;
}
