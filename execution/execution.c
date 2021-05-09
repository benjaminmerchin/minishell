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

	a->dollar_question = 0;
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
	a->dollar_question = 0;
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

	a->dollar_question = 0;
	lst = a->lst_env;
	update_pwd(a, i);
	while (a->raw[*i + 1].str && ft_strncmp(a->raw[*i].str, a->raw[*i + 1].str, 10) == 0 && ft_strlen(a->raw[*i + 1].str) == 3)
		(*i)++;
	if (!(a->raw[*i + 1].str == 0 || a->raw[*i + 1].type == '|' || a->raw[*i + 1].type == ';'))
	{
		a->dollar_question = 1;
		ft_putstr_fd("env: ", a->raw[*i].fd_output);
		ft_putstr_fd(a->raw[*i + 1].str, a->raw[*i].fd_output);
		ft_putstr_fd(": No such file or directory\n", a->raw[*i].fd_output);
		while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
			(*i)++;
		return ;
	}
	else
		a->dollar_question = 0;
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
		a->dollar_question = 1;
		ft_putstr_fd("\033[033m", 1);
		ft_putstr_fd(MINISHELL_NAME, a->raw[*i].fd_output);
		ft_putstr_fd(": export: `", a->raw[*i].fd_output);
		ft_putstr_fd(str, a->raw[*i].fd_output);
		ft_putstr_fd("': not a valid identifier\n", a->raw[*i].fd_output);
		ft_putstr_fd("\033[0m", 1);
		return(-1);
	}
	j++;
	return (j);
}

void	command_not_found(t_a *a, int *i)
{
	a->dollar_question = 127;
	ft_putstr_fd("\033[031m", 1);
	ft_putstr_fd(MINISHELL_NAME, a->raw[*i].fd_output);
	ft_putstr_fd(": ", a->raw[*i].fd_output);
	ft_putstr_fd(a->raw[*i].str, a->raw[*i].fd_output);
	ft_putstr_fd(": command not found\n", a->raw[*i].fd_output);
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
		(*i)++;
	ft_putstr_fd("\033[0m", 1);
}

void	add_env(t_a *a, int *i)
{
	int ret;
	t_list *lst;

	a->dollar_question = 0;
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
	a->dollar_question = 0;
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
	a->dollar_question = 0;
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
		ft_putstr_fd("\033[031m", a->raw[*i].fd_output);
		ft_putstr_fd(MINISHELL_NAME, a->raw[*i].fd_output);
		ft_putstr_fd(": cd: ", a->raw[*i].fd_output);
		ft_putstr_fd(a->raw[*i].str, a->raw[*i].fd_output);
		ft_putstr_fd(": No such file or directory\033\n", a->raw[*i].fd_output);
		a->dollar_question = 127;		
	}
	else
		a->dollar_question = 0;
	update_pwd(a, i);
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
		(*i)++;
}

void	ft_execution_function(t_a *a)
{
	//ft_putstr_fd(a->raw[a->i].str, 1);
	if (ft_strncmp(a->raw[a->i].str, "exit", 10) == 0)
		ft_exit_clean(a, "");
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
		fork_wait_execute(a, &a->i); // here try to find the executables
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

void	ft_execution_backup(t_a *a)
{
	int status;
	int k;


	//first we want to link the correct fd so go through the list
	//we also replace the $VAR by their values
	//each token must have its correct fd
	temporary_set_all_input_to_0_and_output_to_1(a);
	while (a->raw[a->i].str)//on boucle entre | ou ;
	{
		k = 0;
		expansion_dup(a, &a->i); // besoin de reset les fd en fin d'appel 
		if (a->raw[a->i].type == '|' || a->raw[a->i].type == ';')
		{
			//ft_pipemanager(a);
			a->i++;
		}
		else
		{
			g_fantaisie = fork();
			k = a->i;
			if (g_fantaisie == 0)
			{
				ft_execution_function(a);
				exit (a->exit_status);
			}
			else if (g_fantaisie < 0)
				ft_exit_clean(a, "Error:\nFork failed\n");
			else
			{
				if (ft_strncmp(a->raw[a->i].str, "exit", 10) == 0)
					exit(0);
				while (!WIFEXITED(status) && !WIFSIGNALED(status))
					waitpid(g_fantaisie, &status, WUNTRACED);
				a->i = k;
				k = ft_dist_to_pipe(a);
				ft_putstr_fd("On a attendu\n", 1);
				if (k != -1)
				{
					a->i = a->i + k;
				}
				a->i++;
			}
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

// TODO DIVERS:
// dup & | & fd < >> >
// ctrl + / ou D ou C (la variable globale signal)
// norme


/*
void	ft_execution_backup(t_a *a)
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
		if (a->raw[i].type == '|' || a->raw[i].type == ';')
		{
			//pipemanager(a);
			i++;
		}
		else if (ft_strncmp(a->raw[i].str, "exit", 10) == 0)
			ft_exit_clean(a, "");
		else if (ft_strncmp(a->raw[i].str, "echo", 10) == 0)
			ft_echo(a, &i);
		else if (ft_strncmp(a->raw[i].str, "cd", 10) == 0)
			ft_cd(a, &i);
		else if (ft_strncmp(a->raw[i].str, "pwd", 10) == 0)
			ft_pwd(a, &i);
		else if (ft_strncmp(a->raw[i].str, "export", 10) == 0)
			ft_export(a, &i);
		else if (ft_strncmp(a->raw[i].str, "unset", 10) == 0)
			ft_unset(a, &i);
		else if (ft_strncmp(a->raw[i].str, "env", 10) == 0)
			ft_env(a, &i);
		else
			fork_wait_execute(a, &i); // here try to find the executables
	}
}
*/

void	ft_pipe_manager(t_a *a)
{
	int 	status;
	int		fd[2];

	pipe(fd);
	g_fantaisie = fork();
	if (g_fantaisie == 0)
	{
		//on est dans gauche
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		//afficher tous les fd ouverts
		ft_execution_function(a);
		exit (a->exit_status);
	}                     
	else if (g_fantaisie > 0)
	{
		//on est dans droite
		ft_putstr_fd("on y rentre ?\n", 1);
		if (ft_strncmp(a->raw[a->i].str, "exit", 10) == 0)
			exit(0);
		waitpid(g_fantaisie, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(g_fantaisie, &status, WUNTRACED);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		a->i += ft_dist_to_pipe(a) + 1;
		ft_execution(a);
	}
	else
	{
		exit(0);
	}
}

void    ft_execution(t_a *a)
{
	temporary_set_all_input_to_0_and_output_to_1(a);
	while (a->raw[a->i].str)//on boucle entre | ou ;
	{
		//replace_var_env_until_next_separator(a, &a->i);
		if (ft_dist_to_pipe(a) != -1)
		{
			ft_pipe_manager(a);
		}
		else
		{
			ft_execution_function(a);
		}
		if (a->raw[a->i].type != 0)
			(a->i)++;
		else
			break;
    }
}
