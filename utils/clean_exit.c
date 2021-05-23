/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:00:55 by user42            #+#    #+#             */
/*   Updated: 2021/03/18 19:04:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cleanstruct(t_a *a)
{
	int		i;

	i = -1;
	while (a->raw[++i].str)
		free(a->raw[i].str);
	free (a->raw);
	if (a->line && !DEBUG)
		free(a->line);
	a->line = NULL;
	a->sep = SEPARATORS;
	ft_fd_closing(a);
}

void	ft_cleantermcaps(t_a *a)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &a->trms);
}

void	ft_exit_clean(t_a *a, char *str)
{
	int	i;

	ft_putstr_fd(str, 2);
	ft_fd_closing(a);
	ft_cleanstruct(a);
	//ft_putnbr(ft_lstsize(a->lst_env));
	ft_lstclear(&(a->lst_env)); // free env list
	if (TERMCAPS)
	{
		i = 0;
		if (a->h)
		{
			while (a->h[i])
			{
				free(a->h[i]);
				i++;
			}
			free(a->h);
		}
		ft_cleantermcaps(a); //clairement ça ne clean pas encore tout
	}
	exit (a->dollar_question);
}

void	ft_move_to_the_end(t_a *a)
{
	while (a->i < a->len_raw)
		a->i++;
}

void	ft_manage_exit_argument(t_a *a)
{
	int	sign;
	int	iter;

	iter = 0;
	sign = 1;
	if (a->raw[a->i + 1].str[iter] == '-')
	{
		sign = -1;
		iter++;
	}
	while (a->raw[a->i + 1].str[iter])
	{
		if (!ft_isdigit(a->raw[a->i + 1].str[iter]))
		{
			ft_putstr_fd("\033[031m", 1);
			ft_putstr_fd(MINISHELL_NAME, 1);
			ft_putstr_fd(": exit: numeric argument required\033\n", 1);
			a->dollar_question = 255;
			ft_exit_clean(a, "");
		}
		iter++;
	}
	a->dollar_question = sign * ft_atoi(a->raw[a->i + 1].str);
	while (a->dollar_question < 0)
		a->dollar_question += 256;
	a->dollar_question = a->dollar_question % 256;
	ft_exit_clean(a, "");
}

void	ft_exit(t_a *a)
{
	if (!a->raw[a->i + 1].type)
		ft_exit_clean(a, "");
	if (a->len_raw > a->i + 2 && a->raw[a->i + 2].type != ';')
	{
		ft_putstr_fd("\033[031m", 1);
		ft_putstr_fd(MINISHELL_NAME, 1);
		ft_putstr_fd(": exit: too many arguments\033\n", 1);
		ft_move_to_the_end(a);
		return ;
	}
	ft_manage_exit_argument(a);
}

void	set_backup_and_exit(t_a *a, char *str)
{
	a->line = a->backup;
	ft_exit_clean(a, str);
}
