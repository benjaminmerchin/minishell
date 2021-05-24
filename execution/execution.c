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

int	content_have_value(char *str)
{
	int	i;

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

void	ft_env_2(t_a *a, int *i)
{
	a->dollar_question = 1;
	ft_putstr_fd("env: ", 1);
	ft_putstr_fd(a->raw[*i + 1].str, 1);
	ft_putstr_fd(": No such file or directory\n", 1);
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' \
	&& a->raw[*i].type != ';')
		(*i)++;
}

void	ft_env(t_a *a, int *i)
{
	t_list	*lst;

	a->dollar_question = 0;
	lst = a->lst_env;
	update_pwd(a, i);
	while (a->raw[*i + 1].str && ft_strncmp(a->raw[*i].str, \
	a->raw[*i + 1].str, 10) == 0 && ft_strlen(a->raw[*i + 1].str) == 3)
		(*i)++;
	if (!(a->raw[*i + 1].str == 0 || a->raw[*i + 1].type == '|' \
	|| a->raw[*i + 1].type == ';'))
	{
		ft_env_2(a, i);
		return ;
	}
	while (lst)
	{
		if (content_have_value(lst->content))
		{
			ft_putstr_fd(lst->content, 1);
			ft_putstr_fd("\n", 1);
		}
		lst = lst->next;
	}
	(*i)++;
}

int	ft_verification_content(char *str, t_a *a, int *i)
{
	int	j;
	int	error;

	(void)i;
	j = 0;
	error = 0;
	while (str[j] != '=' && str[j] != '\0')
	{
		if ((j > 0 && !(ft_isalnum(str[j]) || str[j] == '_')) \
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
		ft_putstr_fd(MINISHELL_NAME, 1);
		ft_putstr_fd(": export: `", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
		ft_putstr_fd("\033[0m", 1);
		return (-1);
	}
	j++;
	return (j);
}

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
	int ret;
	t_list *lst;

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

	(void)i;
	lst = a->lst_env;
	while (lst)
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (lst->content[j] != '=' && lst->content[j] != '\0')
		{
			ft_putchar_fd(lst->content[j], 1);
			j++;
		}
		if (lst->content[j] == '=')
		{
			ft_putchar_fd('=', 1);
			j++;
			ft_putchar_fd('"', 1);
			ft_putstr_fd(lst->content + j, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putstr_fd("\n", 1);
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

void		join_me_if_im_quotation_marks(t_a *a, int *i, int ret)
{
	char *temp;
	int num;
	
	if (a->raw[*i + 1].type == '\'' || a->raw[*i + 1].type == '"')
	{
		if (a->raw[*i].str[ret] != '\0')
			return ;
		num = *i;
		temp = ft_strjoin_libft(a->raw[*i].str, a->raw[*i + 1].str);
		remove_token_from_list(a, num + 1);
		free(a->raw[*i].str);
		a->raw[*i].str = temp;
	}
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
		{
			join_me_if_im_quotation_marks(a, i, ret);
			add_me_if_i_do_not_exist_yet(a, i, ret);
		}
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
		ft_putstr_fd("\033[031m", 1);
		ft_putstr_fd(MINISHELL_NAME, 1);
		ft_putstr_fd(": cd: ", 1);
		ft_putstr_fd(a->raw[*i].str, 1);
		ft_putstr_fd(": No such file or directory\033\n", 1);
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
	int 	status;
	int		fd[2];
	int		temp;
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		//on est dans gauche
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
		//on est dans droite
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
	{
		exit(a->dollar_question);
	}
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
