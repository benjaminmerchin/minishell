/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaverne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 12:41:44 by gtaverne          #+#    #+#             */
/*   Updated: 2021/05/24 12:41:47 by gtaverne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_fd_closing(t_a *a)
{
	dup2(a->fd_output, 1);
	dup2(a->fd_input, 0);
}

void	ft_attributefd(t_a *a, int *i, int in_or_out)
{
	int		fd;

	if (in_or_out == 0)
	{
		fd = open(a->raw[*i + 1].str, O_RDONLY, 0644);
		if (fd < 0)
		{
			ft_putstr(MINISHELL_NAME);
			ft_putstr(a->raw[*i + 1].str);
			ft_putstr(": Aucun fichier ou dossier de ce type\n");
		}
		close(fd);
	}
}

int	is_sep_redir(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_redirection_in(t_a *a)
{
	a->dollar_question = 2;
	ft_putstr_fd("\033[033m", 1);
	ft_putstr_fd(MINISHELL_NAME, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd("Syntax error, unexpected newline, | or ;\n", 1);
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
	ft_putstr_fd(": No such file or directory\n", 1);
	ft_putstr_fd("\033[0m", 1);
	g_fantaisie = -25;
	a->i = k;
	while (a->raw[a->i].type)
	{
		if (a->raw[a->i].type == ';' || a->raw[a->i].type == '|')
			return ;
		a->i++;
	}
}
