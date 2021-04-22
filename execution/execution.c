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

void	update_pwd(t_a *a, int *i)
{
	t_list *lst;
	char	buff[10000];
	char	*ptr;

	(void)i;
	lst = a->lst_env;
	ptr = getcwd(buff, 10000);
	if (!ptr)
		return ;
	while (lst)
	{
		if  (ft_strncmp("PWD=", lst->content, 4) == 0)
		{
			free(lst->content);
			lst->content = ft_strjoin_libft("PWD=", ptr);
			return ;
		}
		lst = lst->next;
	}
}

void	ft_echo(t_a *a, int *i)
{
	int	v_b_bn; //variable boolean to manage the -n flag
	int	n_begin; //-n flag only accepted at the beginning

	(*i)++;
	v_b_bn = 1;
	n_begin = 0;
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
	{
		if (n_begin == 1 && a->raw[*i].space_before == 1)
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
}

void	ft_parsenv_fd(t_a *a, int fd)
{
	t_list *lst;

	lst = a->lst_env;
	while (lst)
	{
		if  (ft_strncmp("PWD=", lst->content, 4) == 0)
		{
			ft_putstr_fd(lst->content + 4, fd);
			return ;
		}
		lst = lst->next;
	}
}

void	ft_pwd(t_a *a, int *i)
{	
	update_pwd(a, i);
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
	update_pwd(a, i);
	while (a->raw[*i + 1].str && ft_strncmp(a->raw[*i].str, a->raw[*i + 1].str, 10) == 0 && ft_strlen(a->raw[*i + 1].str) == 3)
		(*i)++;
	if (!(a->raw[*i + 1].str == 0 || a->raw[*i + 1].type == '|' || a->raw[*i + 1].type == ';'))
	{
		ft_putstr_fd("env: ", a->raw[*i].fd_output);
		ft_putstr_fd(a->raw[*i + 1].str, a->raw[*i].fd_output);
		ft_putstr_fd(": No such file or directory\n", a->raw[*i].fd_output);
		while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
			(*i)++;
		return ;
	}
	while (lst)
	{
		if (content_have_value(lst->content))
		{
			ft_putstr_fd(lst->content, a->raw[*i].fd_output);
			ft_putstr_fd("\n", a->raw[*i].fd_output);
		}
		lst = lst->next;
	}
	(*i)++;
}

void	ft_work_in_progress(t_a *a, int *i)
{
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
		(*i)++;
	ft_putstr_fd("Work in progress for this command\n", 1);
}

int		ft_verification_content(char *str, t_a *a, int *i)
{
	int j;
	int error;

	j = 0;
	error = 0;
	while (str[j] != '=' && str[j] != '\0')
	{
		if ((j > 0 && !(ft_isalnum(str[j]) || str[j] == '_'))
		|| (j == 0 && !(ft_isalpha(str[j]) || str[j] == '_')))
		{
			error = 1;
			break ;
		}
		j++;
	}
	if (j == 0 || error == 1)
	{
		ft_putstr_fd(MINISHELL_NAME, a->raw[*i].fd_output);
		ft_putstr_fd(": export: `", a->raw[*i].fd_output);
		ft_putstr_fd(str, a->raw[*i].fd_output);
		ft_putstr_fd("': not a valid identifier\n", a->raw[*i].fd_output);
		return(-1);
	}
	j++;
	return (j);
}

void	command_not_found(t_a *a, int *i)
{
	ft_putstr_fd(MINISHELL_NAME, a->raw[*i].fd_output);
	ft_putstr_fd(": ", a->raw[*i].fd_output);
	ft_putstr_fd(a->raw[*i].str, a->raw[*i].fd_output);
	ft_putstr_fd(": command not found\n", a->raw[*i].fd_output);
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
		(*i)++;
}

void	add_env(t_a *a, int *i)
{
	int ret;
	t_list *lst;

	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
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
	int j;

	j = 0;
	while (a->raw[*i].str[j] != '\0' && a->raw[*i].str[j] != '=')
		j++;
	if (a->raw[*i].str[j] == '=' && j != 0)
		add_env(a, i);
	else
		command_not_found(a, i);
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

void		add_me_if_i_do_not_exist_yet(t_a *a, int *i, int ret)
{
	int	found;
	t_list *lst;

	lst = a->lst_env;
	found = 0;
	while (lst && found == 0)
	{
		if  (ft_strncmp(a->raw[*i].str, lst->content, ret) == 0)
		{
			free(lst->content);
			lst->content = ft_strdup(a->raw[*i].str);
			found = 1;
		}
		lst = lst->next;
	}
	if (found == 0)
		ft_lstadd_back(&(a->lst_env), ft_lstnew(ft_strdup(a->raw[*i].str)));
}

void		ft_export(t_a *a, int *i)
{
	int	ret;

	(*i)++;
	update_pwd(a, i);
	if (a->raw[*i].str == 0 || a->raw[*i].type == '|' || a->raw[*i].type == ';')
		ft_declare_print_export(a, i);
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
	{
		ret = ft_verification_content(a->raw[*i].str, a, i);
		if (ret > 0)
			add_me_if_i_do_not_exist_yet(a, i, ret);
		(*i)++;
	}
}

void		remove_me_if_i_exist(t_a *a, int *i, int ret)
{
	t_list *lst;

	lst = a->lst_env;
	while (lst)
	{
		if  (ft_strncmp(a->raw[*i].str, lst->content, ret) == 0)
		{
			free(lst->content);
			lst->content = ft_strdup(a->raw[*i].str);
			return ;
		}
		lst = lst->next;
	}
}

void	ft_unset(t_a *a, int *i)
{
	int ret;
	
	(*i)++;
	if (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
	{
		ret = ft_verification_content(a->raw[*i].str, a, i);
		if (ret > 0)
			remove_me_if_i_exist(a, i, ret);;
		(*i)++;
	}
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
		(*i)++;
}

void	find_home_and_replace_cd_with_home_path(t_a *a, int *i)
{
	t_list *lst;

	(*i)--;
	lst = a->lst_env;
	while (lst)
	{
		if  (ft_strncmp("HOME=", lst->content, 5) == 0)
		{
			free(a->raw[*i].str);
			a->raw[*i].str = ft_strdup(lst->content + 5);
			return ;
		}
		lst = lst->next;
	}
}

void	ft_cd(t_a *a, int *i)
{	
	int ret;

	(*i)++;
	update_pwd(a, i);
	if (a->raw[*i].str == 0 || a->raw[*i].type == '|' || a->raw[*i].type == ';')
		find_home_and_replace_cd_with_home_path(a, i);
	ret = chdir(a->raw[*i].str);
	if (ret < 0)
	{
		ft_putstr_fd(MINISHELL_NAME, a->raw[*i].fd_output);
		ft_putstr_fd(": cd: ", a->raw[*i].fd_output);
		ft_putstr_fd(a->raw[*i].str, a->raw[*i].fd_output);
		ft_putstr_fd(": No such file or directory\n", a->raw[*i].fd_output);		
	}
	update_pwd(a, i);
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
		(*i)++;
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
		expansion_dup(a, &i); // besoin de reset les fd en fin d'appel 
		if (a->raw[i].type == '|' || a->raw[i].type == ';') //faire l'expansion ici, juste les $ et les // ou ''""
			i++;
		else if (ft_strncmp(a->raw[i].str, "exit", 10) == 0) //80%
			ft_exit_clean(a, "");
		else if (ft_strncmp(a->raw[i].str, "echo", 10) == 0) //80%
			ft_echo(a, &i);
		else if (ft_strncmp(a->raw[i].str, "cd", 10) == 0) //80%
			ft_cd(a, &i);
		else if (ft_strncmp(a->raw[i].str, "pwd", 10) == 0) //80%
			ft_pwd(a, &i);
		else if (ft_strncmp(a->raw[i].str, "export", 10) == 0) //80%
			ft_export(a, &i);
		else if (ft_strncmp(a->raw[i].str, "unset", 10) == 0) //80%
			ft_unset(a, &i);
		else if (ft_strncmp(a->raw[i].str, "env", 10) == 0) //80%
			ft_env(a, &i);
		else
			fork_wait_execute(a, &i); // here try to find the executables
	}
}

//dulpicate fd before fork in order to be able to restore them
//https://youtu.be/ceNaZzEoUhk watch this video for pipes

//Command list:
//Implementer des builtins
	//echo (-n) cd pwd export unset env exit
//"Chercher et lancer le bon executable (basé sur une variable d’environnement PATH ou en utilisant un path absolu), comme dans bash"
	//this means being able to execute through a fork the commends that we will try to get in the path (ls, ...)

// TODO DIVERS:
// dup & | & fd < >> >
// $env $replace
// management of the \' or \" or \\\' etc
// $? error management in the fork part
// ctrl + / ou D ou C (la variable globale signal)
// norme
