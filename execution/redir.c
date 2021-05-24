/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaverne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:41:30 by gtaverne          #+#    #+#             */
/*   Updated: 2021/05/24 12:41:33 by gtaverne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_token_from_list(t_a *a, int i)
{
	int	j;

	j = 0;
	free(a->raw[i].str);
	while (a->raw[i + j + 1].type)
	{
		a->raw[i + j].type = a->raw[i + j + 1].type;
		a->raw[i + j].str = a->raw[i + j + 1].str;
		a->raw[i + j].space_before = a->raw[i + j + 1].space_before;
		j++;
	}
	(a->len_raw)--;
	a->raw[i + j].type = 0;
	a->raw[i + j].str = 0;
}

int	ft_redirection_out(t_a *a, int k, int fd)
{
	if (a->raw[k].type == '>')
	{
		fd = open(a->raw[k + 1].str, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (fd <= 0)
			ft_exit_clean(a, "Couldn't create file \n");
		dup2(fd, 1);
		close(fd);
		remove_token_from_list(a, k);
		remove_token_from_list(a, k);
	}
	else if (a->raw[k].type == '#')
	{
		fd = open(a->raw[k + 1].str, O_RDWR | O_APPEND | O_CREAT, 0644);
		if (fd <= 0)
			ft_exit_clean(a, "Couldn't create file \n");
		dup2(fd, 1);
		close(fd);
		remove_token_from_list(a, k);
		remove_token_from_list(a, k);
	}
	if (a->raw[k].type != '#' && a->raw[k].type != '>')
		k++;
	return (k);
}

void	ft_redirection_in(t_a *a)
{
	a->dollar_question = 2;
	ft_putstr_fd("\033[033m", 1);
	ft_putstr_fd(MINISHELL_NAME, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd("Syntax error, unexpected newline or ;\n", 1);
	ft_putstr_fd("\033[0m", 1);
	while (a->raw[a->i].type)
		a->i++;
	a->i--;
	g_fantaisie = -25;
}

void	ft_redirection_in2(t_a *a, int k)
{
	a->dollar_question = 1;
	ft_putstr_fd("\033[033m", 1);
	ft_putstr_fd(MINISHELL_NAME, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(a->raw[k + 1].str, 1);
	ft_putstr_fd("': No such file or directory\n", 1);
	ft_putstr_fd("\033[0m", 1);
	while (a->raw[a->i].type)
		a->i++;
	g_fantaisie = -25;
}

void	ft_redirection(t_a *a)
{
	int	k;
	int	fd;

	k = a->i;
	while (a->raw[k].type && a->raw[k].type != ';' && a->raw[k].type != '|')
	{
		if (a->raw[k].type == '<')
		{
			if (!a->raw[k + 1].type || a->raw[k + 1].type == ';')
			{
				ft_redirection_in(a);
				return ;
			}
			fd = open(a->raw[k + 1].str, O_RDONLY, 0644);
			if (fd <= 0)
				ft_redirection_in2(a, k);
			dup2(fd, 0);
			close(fd);
			remove_token_from_list(a, k);
			remove_token_from_list(a, k);
		}
		k = ft_redirection_out(a, k, fd);
	}
}
