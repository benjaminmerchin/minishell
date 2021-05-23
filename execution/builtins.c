/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:21:54 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 23:21:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_backup_stdinandout(t_a *a)
{
	a->fd_input = dup(0);
	a->fd_output = dup(1);
}

void	update_pwd(t_a *a, int *i)
{
	t_list	*lst;
	char	buff[10000];
	char	*ptr;

	(void)i;
	lst = a->lst_env;
	ptr = getcwd(buff, 10000);
	if (!ptr)
		return ;
	while (lst)
	{
		if (ft_strncmp("PWD=", lst->content, 4) == 0)
		{
			free(lst->content);
			lst->content = ft_strjoin_libft("PWD=", ptr);
			return ;
		}
		lst = lst->next;
	}
}

void	ft_echo(t_a *a, int *i)
{
	int	v_b_bn;
	int	n_begin;

	(*i)++;
	v_b_bn = 1;
	n_begin = 0;
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' \
	&& a->raw[*i].type != ';')
	{
		if (n_begin == 1 && a->raw[*i].space_before == 1)
			ft_putstr_fd(" ", 1);
		if (ft_strncmp(a->raw[*i].str, "-n", 10) == 0 && n_begin == 0)
			v_b_bn = 0;
		else
		{
			ft_putstr_fd(a->raw[*i].str, 1);
			n_begin = 1;
		}
		(*i)++;
	}
	if (v_b_bn == 1)
		ft_putchar_fd('\n', 1);
	a->dollar_question = 0;
}

void	ft_parsenv_fd(t_a *a, int fd)
{
	t_list	*lst;

	lst = a->lst_env;
	while (lst)
	{
		if (ft_strncmp("PWD=", lst->content, 4) == 0)
		{
			ft_putstr_fd(lst->content + 4, fd);
			return ;
		}
		lst = lst->next;
	}
}

void	ft_pwd(t_a *a, int *i)
{	
	a->dollar_question = 0;
	update_pwd(a, i);
	ft_parsenv_fd(a, 1);
	ft_putchar_fd('\n', 1);
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' \
	&& a->raw[*i].type != ';')
		(*i)++;
}
