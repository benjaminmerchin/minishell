/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:21:54 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 23:21:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	j_0_error_1(char *str, t_a *a)
{
	a->dollar_question = 1;
	ft_putstr_fd("\033[033m", 1);
	ft_putstr_fd(MINISHELL_NAME, 1);
	ft_putstr_fd(": export: `", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd("': not a valid identifier\n", 1);
	ft_putstr_fd("\033[0m", 1);
	return (-1);
}

int	ft_verification_content(char *str, t_a *a, int *i)
{
	int	j;
	int	error;

	(void)i;
	j = 0;
	error = 0;
	while (str[j] != '=' && str[j] != '\0')
	{
		if ((j > 0 && !(ft_isalnum(str[j]) || str[j] == '_')) \
		|| (j == 0 && !(ft_isalpha(str[j]) || str[j] == '_')))
		{
			error = 1;
			break ;
		}
		j++;
	}
	if (j == 0 || error == 1)
		return (j_0_error_1(str, a));
	j++;
	return (j);
}

void	add_me_if_i_do_not_exist_yet(t_a *a, int *i, int ret)
{
	int		found;
	t_list	*lst;

	lst = a->lst_env;
	found = 0;
	ret--;
	while (lst && found == 0)
	{
		if (ft_strncmp(a->raw[*i].str, lst->content, ret) == 0
			&& (lst->content[ret] == '=' || lst->content[ret] == '\0'))
		{
			if (lst->content[ret] == '=' && a->raw[*i].str[ret] == '\0')
			{
				found = 1;
				break ;
			}
			free(lst->content);
			lst->content = ft_strdup(a->raw[*i].str);
			found = 1;
		}
		lst = lst->next;
	}
	if (found == 0)
		ft_lstadd_back(&(a->lst_env), ft_lstnew(ft_strdup(a->raw[*i].str)));
}

void	join_me_if_im_quotation_marks(t_a *a, int *i, int ret)
{
	char	*temp;
	int		num;

	if (a->raw[*i + 1].type == '\'' || a->raw[*i + 1].type == '"')
	{
		if (a->raw[*i].str[ret] != '\0')
			return ;
		num = *i;
		temp = ft_strjoin_libft(a->raw[*i].str, a->raw[*i + 1].str);
		remove_token_from_list(a, num + 1);
		free(a->raw[*i].str);
		a->raw[*i].str = temp;
	}
}

void	ft_export(t_a *a, int *i)
{
	int	ret;

	(*i)++;
	update_pwd(a, i);
	a->dollar_question = 0;
	if (a->raw[*i].str == 0 || a->raw[*i].type == '|' || a->raw[*i].type == ';')
		ft_declare_print_export(a, i);
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|'
		&& a->raw[*i].type != ';')
	{
		ret = ft_verification_content(a->raw[*i].str, a, i);
		if (ret > 0)
		{
			join_me_if_im_quotation_marks(a, i, ret);
			add_me_if_i_do_not_exist_yet(a, i, ret);
		}
		(*i)++;
	}
}
