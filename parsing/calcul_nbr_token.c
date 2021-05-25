/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul_nbr_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:21:54 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 23:21:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_sep(char c, t_a *a)
{
	int	i;

	i = 0;
	while (a->sep[i])
	{
		if (c == a->sep[i])
			return (1);
		i++;
	}
	return (0);
}

void	calcul_k_2(t_a *a, int i)
{
	if (a->line[i] == ' ')
	{
		while (is_sep(a->line[i + 1], a) && a->line[i] == ' ')
			(a->line)++;
	}
}

void	calcul_k_3(t_a *a, int *i, int *counter)
{
	if (a->line[0] == ' ')
		(a->line)++;
	if (a->line[0] == '\0')
		return ;
	*counter = 0;
	while (!is_sep(a->line[*counter], a) && a->line[*counter] != '\0')
		(*counter)++;
	while (*counter > 0)
	{
		(*i)++;
		(*counter)--;
		(a->line)++;
	}
	*i = 0;
}

void	calcul_init_backup(t_a *a, int *i, int *k)
{
	*i = 0;
	*k = 0;
	a->backup = a->line;
	a->backup_backup = ft_strdup(a->line);
}

int	calcul_k(t_a *a)
{
	int		i;
	int		k;
	int		counter;

	replace_antislash_and_content_by_value(a);
	calcul_init_backup(a, &i, &k);
	while (a->ending_quote && a->line[i])
	{
		calcul_k_2(a, i);
		if (a->line[i] == ' ' || !is_sep(a->line[i], a))
			calcul_k_3(a, &i, &counter);
		else if (ft_strlen(a->line) > 1
			& a->line[0] == '>' && a->line[1] == '>')
			calcul_k_4(a);
		else if (a->line[i] == '|' || a->line[i] == ';'
			|| a->line[i] == '<' || a->line[i] == '>')
			(a->line)++;
		else if (a->line[i] == '"' || a->line[i] == '\'')
			calcul_k_5(a, &i, &counter);
		k++;
	}
	a->line = a->backup;
	calcul_k_7(a);
	a->line = a->backup_backup;
	return (k);
}
