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

void	temporary_set_all_input_to_0_and_output_to_1(t_a *a)
{
	int i;

	i = 0;
	while (a->raw[i].str)
	{
		a->raw[i].fd_input = 0;
		a->raw[i].fd_output = 1;
		i++;
	}
	a->raw[i].fd_input = 0;
	a->raw[i].fd_output = 1;
}

void	ft_echo(t_a *a, int *i)
{
	int	v_b_bn; //variable boolean to manage the -n flag
	int	n_begin; //-n flag only accepted at the beginning
	(void)a;

	(*i)++;
	v_b_bn = 1;
	n_begin = 0;
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
	{
		if (n_begin == 1)
			ft_putstr_fd(" ", a->raw[*i].fd_output);
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
		ft_putchar_fd('\n', a->raw[*i - 1].fd_output);
	//write(1, "@@@@@@@@@@", 10);
}

void	ft_parsenv_fd(t_a *a, int fd)
{
	int i;

	i = -1;
	while (a->env[++i])
	{
		if (ft_strncmp(a->env[i], "PWD=", 4) == 0)
		{
			ft_putstr_fd(a->env[i] + 4, fd);
			return ;
		}
	}
}

void	ft_pwd(t_a *a, int *i)
{	
	ft_parsenv_fd(a, a->raw[*i].fd_output);
	ft_putchar_fd('\n', a->raw[*i].fd_output);
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
		(*i)++;
}

void	ft_env(t_a *a, int *i)
{
	int j;

	j = 0;
	while (a->env[j])
	{
		ft_putstr_fd(a->env[j], a->raw[*i].fd_output);
		ft_putstr_fd("\n", a->raw[*i].fd_output);
		j++;
	}
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
		(*i)++;
}

void	ft_work_in_progress(t_a *a, int *i)
{
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
		(*i)++;
	ft_putstr_fd("Work in progress for this command\n", 1);
}

void	command_not_found(t_a *a, int *i)
{
	/*if (a->raw[*i].fd_output == 1 || a->raw[*i].fd_output == 2)
		ft_putstr_fd("\n", a->raw[*i].fd_output);*/
	ft_putstr_fd("minishell: ", a->raw[*i].fd_output);
	ft_putstr_fd(a->raw[*i].str, a->raw[*i].fd_output);
	ft_putstr_fd(": command not found\n", a->raw[*i].fd_output);
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
		(*i)++;
}

int		does_this_command_exist(t_a *a, int *i)
{
	(void)a;
	(void)i;
	return (0);
}

void	dup_fork_wait_execute(t_a *a, int *i)
{
	(void)a;
	(void)i;
	return ;
}

void	ft_execution(t_a *a)
{
	int i;

	i = 0;
	//first we want to link the correct fd so go through the list
	//we also replace the $VAR by their values
	//each token must have its correct fd

	temporary_set_all_input_to_0_and_output_to_1(a);

	//we loop through the commands
		//we execute the build in commands if we can
		//we dup, fork and execute for he others commands
	while (a->raw[i].str)//on boucle entre | ou ;
	{
		if (a->raw[i].type == '|' || a->raw[i].type == ';')
			i++;
		else if (ft_strncmp(a->raw[i].str, "exit", 10) == 0) //70%
			ft_exit_clean(a, "");
		else if (ft_strncmp(a->raw[i].str, "echo", 10) == 0) //70%
			ft_echo(a, &i);
		else if (ft_strncmp(a->raw[i].str, "cd", 10) == 0)
			ft_work_in_progress(a, &i);
		else if (ft_strncmp(a->raw[i].str, "pwd", 10) == 0) //80%
			ft_pwd(a, &i);
		else if (ft_strncmp(a->raw[i].str, "export", 10) == 0)
			ft_work_in_progress(a, &i);
		else if (ft_strncmp(a->raw[i].str, "unset", 10) == 0)
			ft_work_in_progress(a, &i);
		else if (ft_strncmp(a->raw[i].str, "env", 10) == 0) //70%
			ft_env(a, &i);
		else
		{
			if (does_this_command_exist(a, &i))
				dup_fork_wait_execute(a, &i); // here try to find the executables
			else
				command_not_found(a, &i);	//90%
		}
	}
}


//dulpicate fd before fork in order to be able to restore them
//https://youtu.be/ceNaZzEoUhk watch this video for pipes

//Command list:
//Implementer des builtins
	//echo (-n) cd pwd export unset env exit
//"Chercher et lancer le bon executable (basé sur une variable d’environnement PATH ou en utilisant un path absolu), comme dans bash"
	//this means being able to execute through a fork the commends that we will try to get in the path (ls, ...)

//TODO DIVERS:
//getcdw : pour obtenir le pwd a update a chaque mouvement
//stat : donne toutes les infos d'un fichier comme un ls
//lstat : same sauf que dans le cas d'un lien donne les infos sur le lien et pas le fichier pointé
//ftat : donne toutes les infos sur un fichier comme un ls, mais cette fois on lui passe en argument le file descriptor
//execve : exécuter un exécutable, avec ses arguments et l'environnement en paramètres
