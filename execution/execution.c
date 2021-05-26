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

void	ft_execution_function(t_a *a)
{
	if (TERMCAPS)
		signal_stuff(a);
	ft_redirection(a);
	if (g_fantaisie == -25)
	{
		g_fantaisie = 1;
		return ;
	}
	if (ft_strncmp(a->raw[a->i].str, "exit", 10) == 0)
		ft_exit(a);
	else if (ft_strncmp(a->raw[a->i].str, "echo", 10) == 0)
		ft_echo(a, &a->i);
	else if (ft_strncmp(a->raw[a->i].str, "cd", 10) == 0)
		ft_cd(a, &a->i);
	else if (ft_strncmp(a->raw[a->i].str, "pwd", 10) == 0)
		ft_pwd(a, &a->i);
	else if (ft_strncmp(a->raw[a->i].str, "export", 10) == 0)
		ft_export(a, &a->i);
	else if (ft_strncmp(a->raw[a->i].str, "unset", 10) == 0)
		ft_unset(a, &a->i);
	else if (ft_strncmp(a->raw[a->i].str, "env", 10) == 0)
		ft_env(a, &a->i);
	else
		fork_wait_execute(a, &a->i);
}

void	ft_pipe_manager(t_a *a)
{
	int		status;
	int		fd[2];
	int		temp;
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
		ft_pipe_manager_pid_0(a, fd);
	else if (pid > 0)
	{
		close(fd[1]);
		temp = dup(0);
		dup2(fd[0], 0);
		if (ft_strncmp(a->raw[a->i].str, "exit", 10) == 0)
			exit(a->dollar_question);
		close(fd[0]);
		ft_pipe_manager_2(a);
		dup2(temp, 0);
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
	else
		exit(a->dollar_question);
}

void	ft_execution_sublevel(t_a *a)
{
	while (a->i < a->len_raw && a->raw[a->i].type != ';')
	{
		if (ft_dist_to_pipe(a) > 0)
		{
			ft_pipe_manager(a);
		}
		else
		{
			ft_execution_function(a);
		}
		(a->i)++;
	}
}

void	ft_execution(t_a *a)
{
	if (a->ending_quote == 0)
	{
		ft_putstr_fd("Error: missing ending quote\n", 2);
		return ;
	}
	ft_between_semicolon(a, &a->i);
	while (a->i < a->len_raw)
	{
		if (ft_dist_to_pipe(a) > 0)
		{
			ft_pipe_manager(a);
		}
		else
		{
			ft_execution_function(a);
		}
		(a->i)++;
		if (a->i < a->len_raw && a->raw[a->i - 1].type == ';')
			ft_between_semicolon(a, &a->i);
	}
}
