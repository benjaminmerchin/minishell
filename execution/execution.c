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

void	command_not_found(t_a *a, int *i)
{
	a->dollar_question = 127;
	ft_putstr("\033[031m");
	ft_putstr(MINISHELL_NAME);
	ft_putstr(": ");
	ft_putstr_fd(a->raw[*i].str, 1);
	ft_putstr_fd(": command not found\n", 1);
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' \
	&& a->raw[*i].type != ';')
		(*i)++;
	ft_putstr_fd("\033[0m", 1);
}

void	add_env(t_a *a, int *i)
{
	int		ret;
	t_list	*lst;

	a->dollar_question = 0;
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' \
	&& a->raw[*i].type != ';')
	{
		ret = ft_verification_content(a->raw[*i].str, a, i);
		if (ret > 0)
		{
			lst = a->lst_env;
			while (lst)
			{
				if  (ft_strncmp(a->raw[*i].str, lst->content, ret) == 0)
				{
					free(lst->content);
					lst->content = ft_strdup(a->raw[*i].str);
				}
				lst = lst->next;
			}
			(*i)++;
		}
		else
			command_not_found(a, i);
	}
}

void	add_env_or_command_not_found(t_a *a, int *i)
{
	int	j;

	j = 0;
	while (a->raw[*i].str[j] != '\0' && a->raw[*i].str[j] != '=')
		j++;
	if (a->raw[*i].str[j] == '=' && j != 0)
		add_env(a, i);
	else
		command_not_found(a, i);
}

void	ft_execution_function(t_a *a)
{
	if(TERMCAPS)
	{
		signal(SIGINT, ft_exit_from_branch);
		signal(SIGQUIT, ft_ctrl_antislash_in_function);
	}
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

int		ft_dist_to_pipe(t_a *a)
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

void	ft_pipe_manager(t_a *a)
{
	int		status;
	int		fd[2];
	int		temp;
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		temp = dup(1);
		dup2(fd[1], 1);
		ft_execution_function(a);
		close(fd[1]);
		dup2(temp, 1);
		exit (a->dollar_question);
	}
	else if (pid > 0)
	{
		close(fd[1]);
		temp = dup(0);
		dup2(fd[0], 0);
		if (ft_strncmp(a->raw[a->i].str, "exit", 10) == 0)
			exit(a->dollar_question);
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
		close(fd[0]);
		a->i += ft_dist_to_pipe(a) + 1;
		ft_execution_sublevel(a);
		dup2(temp, 0);
	}
	else
		exit(a->dollar_question);
}

void	ft_execution_sublevel(t_a *a)
{
	while (a->i < a->len_raw && a->raw[a->i].type != ';')//on boucle entre ;
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
