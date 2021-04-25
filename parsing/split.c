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

void	manage_some_tokens(t_a *a, int *i, int *k)
{
	a->raw[*k].type = a->line[*i];
	a->raw[*k].str = malloc(sizeof(char) * 2);
	if (!a->raw[*k].str)
		set_backup_and_exit(a, "Error\nMalloc Failed\n");
	a->raw[*k].str[0] = a->line[*i];
	a->raw[*k].str[1] = 0;
	(a->line)++;
}

void	manage_simple_quote(t_a *a, int *i, int *k, int *counter)
{
	(a->line)++;
	(*counter) = 0;
	while (a->line[*counter] != '\'' && a->line[*counter] != '\0')
		(*counter)++;
	if (a->line[*counter] == '\0')
		set_backup_and_exit(a, "Error\nEnding quote missing\n");
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

void	manage_quotes(t_a *a, int *i, int *k, int *counter)
{
	a->raw[*k].type = a->line[*i];
	if (a->line[*i] == '"')
	{
		(a->line)++;
		*counter = 0;
		while (a->line[*counter] != '"' && a->line[*counter] != '\0')
			(*counter)++;
		if (a->line[*counter] == '\0')
			set_backup_and_exit(a, "Error\nEnding quote missing\n");
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
	else
		manage_simple_quote(a, i, k, counter);
	(a->line)++;
}

void	increase_k_and_set_type_str_to_0(t_a *a, int *k)
{
	(*k)++;
	a->raw[*k].str = 0;
	a->raw[*k].type = 0;
}

void	ft_split_sh(t_a *a)
{
	int		i;
	int		k;
	int		counter;

	if (!(a->raw = malloc(sizeof(*a->raw) * (1 + calcul_k(a)))))
		ft_exit_clean(a, "Error\nMalloc Failed\n");
	replace_antislash_and_content_by_value(a);
	init_split_and_backup(a, &i, &k);
	while (a->line[i])
	{
		skip_spaces(a, &i, &k);
		if (a->line[i] == ' ' || !is_sep(a->line[i], a))
			manage_text(a, &i, &k, &counter);
		else if (ft_strlen(a->line) > 1
		&& a->line[0] == '>' && a->line[1] == '>')
			manage_double_greater_than_sign(a, &k);
		else if (a->line[i] == '|' || a->line[i] == ';'
		|| a->line[i] == '<' || a->line[i] == '>')
			manage_some_tokens(a, &i, &k);
		else if (a->line[i] == '"' || a->line[i] == '\'')
			manage_quotes(a, &i, &k, &counter);
		replace_value_by_content(a->raw[k].str);
		increase_k_and_set_type_str_to_0(a, &k);
	}
	a->line = a->backup;
}
