/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:21:54 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 23:21:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_dist_to_pipe(t_a *a)
{
	int	k;

	k = 0;
	while (a->raw[a->i + k].str && a->raw[a->i + k].type != '|'
		&& a->raw[a->i + k].type != ';')
		k++;
	if (a->raw[a->i + k].type == '|')
		return (k);
	else
		return (-1);
}

void	ft_pipe_manager_pid_0(t_a *a, int fd[2])
{
	int	temp;

	close(fd[0]);
	temp = dup(1);
	dup2(fd[1], 1);
	ft_execution_function(a);
	close(fd[1]);
	dup2(temp, 1);
	exit (a->dollar_question);
}

void	ft_pipe_manager_2(t_a *a)
{
	a->i += ft_dist_to_pipe(a) + 1;
	ft_execution_sublevel(a);
}

void	signal_stuff(t_a *a)
{
	(void)a;
	signal(SIGINT, ft_exit_from_branch);
	signal(SIGQUIT, ft_ctrl_antislash_in_function);
}
