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

void	ft_redirection_out(t_a *a, int k)
{
	int	fd;

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
}

int	ft_fd_neg_questionmark(int fd, t_a *a, int k)
{
	if (fd <= 0)
	{
		ft_redirection_in2(a, k);
		return (1);
	}
	return (0);
}

void	remove_two_token_from_list(t_a *a, int k)
{
	remove_token_from_list(a, k);
	remove_token_from_list(a, k);
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
			if (ft_fd_neg_questionmark(fd, a, k) == 1)
				return ;
			dup2(fd, 0);
			close(fd);
			remove_two_token_from_list(a, k);
		}
		else
			ft_redirection_out(a, k);
		if (!is_sep_redir(a->raw[k].type, ";|#><"))
			k++;
	}
}
