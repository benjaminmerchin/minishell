/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_replacement.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:00:55 by user42            #+#    #+#             */
/*   Updated: 2021/03/18 19:04:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	join_before_env_after(t_a *a, int j, int k, char *src)
{
	int		m;
	int		n;
	int		o;
	char	*temp;

	m = -1;
	n = 0;
	temp = malloc(sizeof(char) * (ft_strlen(a->raw[j].str) \
	- a->ret + 1 + ft_strlen(src)));
	while (++m < k)
		temp[m] = a->raw[j].str[m];
	o = m;
	while (n < ft_strlen(src))
		temp[m++] = src[n++];
	while (a->raw[j].str[o + a->ret])
	{
		temp[m] = a->raw[j].str[o + a->ret];
		m++;
		o++;
	}
	temp[m] = '\0';
	free(a->raw[j].str);
	a->raw[j].str = temp;
}

void	replace_me_if_you_find_me(t_a *a, int j, int k)
{
	t_list	*lst;
	int		l;
	char	*temp;

	k++;
	temp = NULL;
	lst = a->lst_env;
	if (a->there_is_dollar_question == 1)
		return (replace_dollar_question(a, temp, j, k));
	while (lst)
	{
		l = 0;
		while (lst->content[l] == a->raw[j].str[l + k] \
		&& a->raw[j].str[l + k] && lst->content[l] && l < a->ret)
			l++;
		if (lst->content[l] == '=' && (a->raw[j].str[l + k] == '\0' \
		|| (ft_isprint(a->raw[j].str[l + k]) && (!ft_isalnum(a->raw[j].str[l \
		+ k]) && a->raw[j].str[l + k] != '_'))) && l > 0)
		{
			join_before_env_after(a, j, k - 1, lst->content + l + 1);
			return ;
		}
		lst = lst->next;
	}
	remove_token_from_content(a, j, k - 1);
}

void	operation_join_remove(t_a *a, int j, int *j_undo)
{
	char	*temp;

	temp = ft_strjoin_libft(a->raw[j - 1].str, a->raw[j].str);
	free(a->raw[j - 1].str);
	a->raw[j - 1].str = temp;
	remove_token_from_list(a, j);
	*j_undo = 1;
}

void	try_to_replace_token_with_env(t_a *a, int j, int *j_undo)
{
	int	k;

	k = 0;
	while (a->raw[j].str && a->raw[j].str[k])
	{
		if (a->raw[j].str[k] == '$' && a->raw[j].str[k + 1] != '\0')
		{
			a->there_is_dollar_question = 0;
			a->ret = verification_content_env(a->raw[j].str + k + 1, a);
			if (a->ret > 0)
				replace_me_if_you_find_me(a, j, k);
			else
				remove_token_from_content(a, j, k);
			if (j > 0 && a->raw[j].type == '"'
				&& a->raw[j - 1].str[ft_strlen(a->raw[j - 1].str) - 1] == '='
				&& a->raw[j].space_before == 0)
				operation_join_remove(a, j, j_undo);
		}
		if (a->raw[j].str && a->raw[j].str[k] == '\0')
			return ;
		k++;
	}
}

void	replace_var_env_until_next_separator(t_a *a, int *i)
{
	int	j;
	int	j_undo;

	j = *i;
	while (a->raw[j].str != 0 && a->raw[j].type != ';')
	{
		j_undo = 0;
		if (a->raw[j].type != '\'')
			try_to_replace_token_with_env(a, j, &j_undo);
		if ((a->raw[j].type == '\'' || a->raw[j].type == '"') && j_undo == 0)
		{
			if (j > 0 && a->raw[j].space_before == 0
				&& a->raw[j - 1].str[ft_strlen(a->raw[j - 1].str) - 1] == '=')
				operation_join_remove(a, j, &j_undo);
		}
		if (j_undo == 1)
		{
			j_undo = 0;
			j--;
		}
		j++;
	}
}
