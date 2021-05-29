/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_replacement_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:00:55 by user42            #+#    #+#             */
/*   Updated: 2021/03/18 19:04:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verification_content_env(char *str, t_a *a)
{
	int	j;
	int	error;

	j = 0;
	error = 0;
	if (str[0] == '?')
	{
		a->there_is_dollar_question = 1;
		return (2);
	}
	while (str[j] != '$' && str[j] != '\0' \
	&& (ft_isalnum(str[j]) || str[j] == '_'))
	{
		if ((j > 0 && !(ft_isalnum(str[j]) || str[j] == '_')) \
		|| (j == 0 && !(ft_isalpha(str[j]) || str[j] == '_')))
		{
			error = 1;
			break ;
		}
		j++;
	}
	j++;
	if (j == 0 || error == 1)
		return (-1);
	return (j);
}

void	remove_token_from_content(t_a *a, int j, int k)
{
	int		m;
	char	*temp;

	(void)k;
	m = 0;
	temp = malloc(sizeof(char) * (ft_strlen(a->raw[j].str) - a->ret + 1));
	while (m < k)
	{
		temp[m] = a->raw[j].str[m];
		m++;
	}
	while (a->raw[j].str[m + a->ret])
	{
		temp[m] = a->raw[j].str[m + a->ret];
		m++;
	}
	temp[m] = '\0';
	free(a->raw[j].str);
	a->raw[j].str = temp;
}

void	replace_dollar_question(t_a *a, char *temp, int j, int k)
{
	temp = ft_itoa(a->dollar_question);
	a->ret = 2;
	join_before_env_after(a, j, k - 1, temp);
	free(temp);
}
