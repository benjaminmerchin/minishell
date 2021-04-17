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

void	temporary_set_all_input_to_0_and_output_to_2(t_a *a)
{
	int i;

	i = 0;
	while (a->raw[i].str)
	{
		a->raw->fd_input = 0;
		a->raw->fd_output = 1;
		i++;
	}
}

void	ft_echo(t_a *a, int *i)
{
	int	v_b_bn; //variable boolean to manage the -n flag
	int	n_begin;

	(*i)++;
	v_b_bn = 1;
	n_begin = 0;
	if (a->raw[*i].fd_output == 1 || a->raw[*i].fd_output == 2)
		ft_putstr_fd("\n", a->raw[*i].fd_output);
	while (a->raw[*i].str != '\0' && a->raw[*i].type != '|' && a->raw[*i].type != ';')
	{
		if (ft_strncmp(a->raw[*i].str, "-n", 10) == 0 && n_begin == 0)
			v_b_bn = 0;
		else
		{
			ft_putstr_fd(a->raw[*i].str, a->raw[*i].fd_output);
			n_begin = 1;
		}
		(*i)++;
	}
	if (v_b_bn == 1)
		ft_putchar_fd('\n', a->raw[*i].fd_output);
}

void	ft_work_in_progress(t_a *a, int *i)
{
	(void)a;
	(void)i;
}

void	command_not_found(t_a *a, int *i)
{
	/*if (a->raw[*i].fd_output == 1 || a->raw[*i].fd_output == 2)
		ft_putstr_fd("\n", a->raw[*i].fd_output);*/
	ft_putstr_fd(a->raw[*i].str, a->raw[*i].fd_output);
	ft_putstr_fd(": command not found\n", a->raw[*i].fd_output);
}

void	ft_execution(t_a *a)
{
	int i;

	i = 0;
	//first we want to link the correct fd so go through the list
	//each token must have its correct fd

	temporary_set_all_input_to_0_and_output_to_2(a);

	//we loop through the commands
		//we execute the build in commands if we can
		//we dup, fork and execute for he others commands
	while (a->raw[i].str)//on boucle entre | ou ;
	{
		if (a->raw[i].type == '|' || a->raw[i].type == ';')
			;
		else if (ft_strncmp(a->raw[i].str, "exit", 10) == 0) //20%
			ft_exit_clean(a, "");
		else if (ft_strncmp(a->raw[i].str, "echo", 10) == 0) //20%
			ft_echo(a, &i);
		else if (ft_strncmp(a->raw[i].str, "cd", 10) == 0)
			ft_work_in_progress(a, &i);
		else if (ft_strncmp(a->raw[i].str, "pwd", 10) == 0)
			ft_work_in_progress(a, &i);
		else if (ft_strncmp(a->raw[i].str, "export", 10) == 0)
			ft_work_in_progress(a, &i);
		else if (ft_strncmp(a->raw[i].str, "unset", 10) == 0)
			ft_work_in_progress(a, &i);
		else if (ft_strncmp(a->raw[i].str, "env", 10) == 0)
			ft_work_in_progress(a, &i);
		else
			command_not_found(a, &i);	//50%
		i++;
	}
}


//dulpicate fd before fork in order to be able to restore them
//https://youtu.be/ceNaZzEoUhk watch this video for pipes

//Command list:
//echo (-n) cd pwd export unset env exit