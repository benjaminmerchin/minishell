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

int content_have_value(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
void	ft_env(t_a *a, int *i)
{
	t_list *lst;

	lst = a->lst_env;
	while (lst)
	{
		if (content_have_value(lst->content))
		{
			ft_putstr_fd(lst->content, a->raw[*i].fd_output);
			ft_putstr_fd("\n", a->raw[*i].fd_output);
		}
		lst = lst->next;
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
	ft_putstr_fd(MINISHELL_NAME, a->raw[*i].fd_output);
	ft_putstr_fd(": ", a->raw[*i].fd_output);
	ft_putstr_fd(a->raw[*i].str, a->raw[*i].fd_output);
	ft_putstr_fd(": command not found\n", a->raw[*i].fd_output);
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
		(*i)++;
}

void	ft_declare_print_export(t_a *a, int *i)
{
	int j;
	t_list *lst;

	lst = a->lst_env;
	while (lst)
	{
		j = 0;
		ft_putstr_fd("declare -x ", a->raw[*i - 1].fd_output);
		while (lst->content[j] != '=' && lst->content[j] != '\0')
		{
			ft_putchar_fd(lst->content[j], a->raw[*i - 1].fd_output);
			j++;
		}
		if (lst->content[j] == '=')
		{
			ft_putchar_fd('=', a->raw[*i - 1].fd_output);
			j++;
			ft_putchar_fd('"', a->raw[*i - 1].fd_output);
			ft_putstr_fd(lst->content + j, a->raw[*i].fd_output);
			ft_putchar_fd('"', a->raw[*i - 1].fd_output);
		}
		ft_putstr_fd("\n", a->raw[*i - 1].fd_output);
		lst = lst->next;
	}
}

int		ft_verification_content(char *str, t_a *a, int *i)
{
	int j;
	int error;

	j = 0;
	error = 0;
	while (str[j] != '=' && str[j] != '\0')
	{
		if (!(ft_isalnum(str[j]) || str[j] == '_'))
		{
			error = 1;
			break ;
		}
		j++;
	}
	j++;
	if (j == 0 || error == 1)
	{
		ft_putstr_fd(MINISHELL_NAME, a->raw[*i].fd_output);
		ft_putstr_fd(": export: `", a->raw[*i].fd_output);
		ft_putstr_fd(str, a->raw[*i].fd_output);
		ft_putstr_fd("': not a valid identifier\n", a->raw[*i].fd_output);
		return(-1);
	}
	return (j);
}

void		add_me_if_i_do_not_exist_yet(t_a *a, int *i, int ret)
{
	t_list *lst;
	(void)i;
	(void)ret;

	lst = a->lst_env;
}

void		ft_export(t_a *a, int *i)
{
	int	ret;

	(*i)++;
	if (a->raw[*i].str == 0 || a->raw[*i].type == '|' || a->raw[*i].type == ';')
		ft_declare_print_export(a, i);
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
	{
		ret = ft_verification_content(a->raw[*i].str, a, i);
		if (ret > 0)
			add_me_if_i_do_not_exist_yet(a, i, ret);
		//on rajoute la value dans la liste
		(*i)++;
	}
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
		else if (ft_strncmp(a->raw[i].str, "pwd", 10) == 0) //30%
			ft_pwd(a, &i);
		else if (ft_strncmp(a->raw[i].str, "export", 10) == 0) 
			ft_export(a, &i);
		else if (ft_strncmp(a->raw[i].str, "unset", 10) == 0)
			ft_work_in_progress(a, &i);
		else if (ft_strncmp(a->raw[i].str, "env", 10) == 0) //70%
			ft_env(a, &i);
		else
		{
			if (does_this_command_exist(a, &i))
				dup_fork_wait_execute(a, &i); // here try to find the executables
			else
				command_not_found(a, &i);	//80% //except if there is an =, it changes env value
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
//getcdw : pour obtenir le pwd a update a chaque mouvement, update le PWD a chaque changement
//stat : donne toutes les infos d'un fichier comme un ls
//lstat : same sauf que dans le cas d'un lien donne les infos sur le lien et pas le fichier pointé
//ftat : donne toutes les infos sur un fichier comme un ls, mais cette fois on lui passe en argument le file descriptor
//execve : exécuter un exécutable, avec ses arguments et l'environnement en paramètres
// dans ;|0, mettre l'input et l'output de la section d'avant