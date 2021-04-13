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

int		is_insep(char c, char *sep)
{
	int i;

	i = 0;
	while (sep[i])
	{
		if (c == sep[i])
			return (1 + i);
		i++;
	}
	return (0);
}

int		ft_wrdlen(char *str, char *sep)
{
	int i;

	i = 0;
	while (!(is_insep(str[i], sep)) && str[i])
		i++;
	return (i);
}

int		ft_wcount(char *str, char *sep)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (!is_insep(str[i], sep) && (i == 0 ||
					is_insep(str[i - 1], sep)))
			res++;
		i++;
	}
	return (res);
}

char	*ft_wrdcpy(char *src, int wlen)
{
	int		i;
	char	*tmp;

	tmp = malloc(sizeof(*tmp) * (wlen + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < wlen)
	{
		tmp[i] = src[i];
		i++;
	}
	tmp[wlen] = 0;
	return (tmp);
}

void	ft_split_sh(t_a *a)
{
	int		i;
	int		k;

	a->raw = malloc(sizeof(*a->raw) * (1 + ft_wcount(a->line, a->sep)));
	if (!a->raw)
		return ;
	i = 0;
	k = 0;
	while (a->line[i])
	{
		if (!(is_insep(a->line[i], a->sep)) && ft_wrdlen(&a->line[i], a->sep))
		{
			a->raw[k].str = ft_wrdcpy(&a->line[i], ft_wrdlen(&a->line[i], a->sep));
			a->raw[k].type = is_insep(a->line[i - 1], a->sep) - 1;
			k++;
			i = i + ft_wrdlen(&a->line[i], a->sep);
		}
		else
			i++;
		if (a->line[i - 1] == '\'' || a->line[i - 1] == '\"')
			a->sep = "\'\"";
		else
			a->sep = " '\"|><;";
	}
	a->raw[k].str = 0;
	return ;
}
