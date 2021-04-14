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

/*int		is_insep(char c, char *sep, t_a *a)
{
	int i;

	i = 0;
	while (sep[i])
	{
		if (c == sep[i])
		{
			if (c == '\'')
				a->sep = "'";
			return (1);
		}
		i++;
	}
	return (0);
}

char		sep_id(char c, char *sep)
{
	int i;

	i = 0;
	while (sep[i])
	{
		if (c == sep[i])
			return (c);
		i++;
	}
	return (0);
}

int		ft_wrdlen(char *str, char *sep, t_a *a)
{
	int i;

	i = 0;
	while (!(is_insep(str[i], sep, a)) && str[i])
		i++;
	return (i);
}

int		ft_wcount(char *str, char *sep, t_a *a)
{
	int i;
	int res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (!is_insep(str[i], sep, a) && (i == 0 || is_insep(str[i - 1], sep, a)))
			res++;
		a->sep = " '\"|><;";
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

	a->raw = malloc(sizeof(*a->raw) * (1 + ft_wcount(a->line, a->sep, a)));
	if (!a->raw)
		return ;
	i = 0;
	k = 0;
	while (a->line[i])
	{
		if (!(is_insep(a->line[i], a->sep, a)) && ft_wrdlen(&a->line[i], a->sep))
		{
			a->raw[k].str = ft_wrdcpy(&a->line[i], ft_wrdlen(&a->line[i], a->sep, a));
			a->raw[k].type = a->last_sep;
			k++;
			i = i + ft_wrdlen(&a->line[i], a->sep, a);
		}
		else
			i++;
		a->sep = " '\"|><;"; // ici on reset le sep
		if (a->line[i - 1] == '\'' || a->line[i - 1] == '\"')
			a->sep = "\'\"";
		else
			a->sep = " '\"|><;";
	}
	a->raw[k].str = 0;
	return ;
}*/


int		is_sep(char c, t_a *a)
{
	int i;

	i = 0;
	while (a->sep[i])
	{
		if (c == a->sep[i])
		{
			if (a->sep[i] == '"')
				a->sep = "\"";
			if (a->sep[i] == '\'')
				a->sep = "'";
			return (1);
		}
		i++;
	}
	return (0);
}

char	*store_my_token(t_a *a, int *i)
{
	int len_counter;
	char *tmp;
	int j;

	j = 0;
	len_counter = 0;
	while (!is_sep(a->line[*i + len_counter], a) && a->line[*i + len_counter] != '\0')
		len_counter++;
	tmp = malloc(sizeof(char) * (len_counter + 1));
	if (!tmp)
		return (NULL);
	write(1, "#", 1);
	ft_putnbr(len_counter);
	write(1, "#", 1);
	while (j < len_counter)
	{
		tmp[j] = a->line[*i];
		j++;
		(*i)++;
	}
	tmp[j] = 0;
	return (tmp);
}

void	ft_split_sh(t_a *a)
{
	int		i; // parcours le string
	int		k; // parcours le tableau de rangement des tokens
	char	*backup_line;

	backup_line = a->line;
	a->raw = malloc(sizeof(*a->raw) * (1 + 1000));
	if (!a->raw)
		return ;
	i = 0;
	k = 0;
	while (a->line[i])
	{
		if (a->line[i] == ' ')
		{
			while (a->line[i + 1] == ' ')
				i++;
			if (is_sep(a->line[i + 1], a))
				i++;
		}
		if (i == 0 && !is_sep(a->line[0], a))
		{
			a->raw[k].type = ' ';
			i--;
		}
		else
			a->raw[k].type = a->line[i];
		i++;
		a->raw[k].str = store_my_token(a, &i);
		k++;
		if (a->line[i] == '\'' || a->line[i] == '"')
		{
			a->sep = " '\"|><;";
			write(1, "@", 1);
			i++;
		}
	}
	a->raw[k].str = 0;
	a->line = backup_line;
	return ;
}
