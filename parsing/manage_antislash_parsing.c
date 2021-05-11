/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_antislash_parsing.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:21:54 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 23:21:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_and_shift(char *temp, int i, char c)
{
	temp[i] = c;
	i++;
	while (temp[i])
	{
		temp[i] = temp[i + 1];
		i++;
	}
}

void	replace_antislash_and_content_by_value2(int i, char *temp)
{
	if (temp[i + 1] == ' ')
		replace_and_shift(temp, i, 1);
	else if (temp[i + 1] == '\'')
		replace_and_shift(temp, i, 2);
	else if (temp[i + 1] == '\\')
		replace_and_shift(temp, i, 3);
	else if (temp[i + 1] == '"')
		replace_and_shift(temp, i, 4);
	else if (temp[i + 1] == '|')
		replace_and_shift(temp, i, 5);
	else if (temp[i + 1] == ';')
		replace_and_shift(temp, i, 6);
	else if (temp[i + 1] == '<')
		replace_and_shift(temp, i, 7);
	else if (temp[i + 1] == '>')
		replace_and_shift(temp, i, 8);
	else if (temp[i + 1] == '\0')
		replace_and_shift(temp, i, '\\');
	else
		replace_and_shift(temp, i, temp[i + 1]);
}

void	replace_antislash_and_content_by_value(t_a *a)
{
	int		i;
	char	*temp;

	i = 0;
	temp = a->line;
	a->lock_quote = 0;
	while (temp[i])
	{
		if (temp[i] == '\'')
		{
			if (a->lock_quote == 0)
				a->lock_quote = 1;
			else
				a->lock_quote = 0;
		}
		if (temp[i] == '\\' && a->lock_quote == 0)
			replace_antislash_and_content_by_value2(i, temp);
		i++;
	}
}

/*
** ' ' = 1
** ''' = 2
** '\' = 3
** '"' = 4
** '|' = 5
** ';' = 6
** '<' = 7
** '>' = 8
*/

void	replace_value_by_content(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 1)
			str[i] = ' ';
		else if (str[i] == 2)
			str[i] = '\'';
		else if (str[i] == 3)
			str[i] = '\\';
		else if (str[i] == 4)
			str[i] = '"';
		else if (str[i] == 5)
			str[i] = '|';
		else if (str[i] == 6)
			str[i] = ';';
		else if (str[i] == 7)
			str[i] = '<';
		else if (str[i] == 8)
			str[i] = '>';
		i++;
	}
}
