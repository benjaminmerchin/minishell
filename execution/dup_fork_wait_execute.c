/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fork_wait_execute.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:00:55 by user42            #+#    #+#             */
/*   Updated: 2021/03/18 19:04:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
(void)a;
(void)i;
*/

char	**put_args_into_an_array(t_a *a, int *i)
{
	char	**table;
	int 	j;

	j = 0;
	while (a->raw[*i + j].str != 0 && a->raw[*i + j].type != '|' && a->raw[*i + j].type != ';')
		j++;
	table = malloc(sizeof(char *) * (j + 1));
	if (! table)
		ft_exit_clean(a, "Error\nMalloc Failed\n");
	j = 0;
	while (a->raw[*i + j].str != 0 && a->raw[*i + j].type != '|' && a->raw[*i + j].type != ';')
	{
		table[j] = a->raw[*i + j].str;
		j++;
	}
	table[j] = NULL;
	return (table);
}

char	**put_aenv_into_an_array(t_a *a, int *i)
{
	char	**table;
	t_list	*lst;
	int		j;
	(void)i;

	j = ft_lstsize(a->lst_env);
	table = malloc(sizeof(char *) * (j + 1));
	if (! table)
		ft_exit_clean(a, "Error\nMalloc Failed\n");
	j = 0;
	lst = a->lst_env;
	while (lst)
	{
		table[j] = lst->content;
		lst = lst->next;
		j++;
	}
	table[j] = NULL;
	return (table);
}

char	*return_str_from_env(t_a *a, char *str)
{
	t_list *lst;

	lst = a->lst_env;
	while (lst)
	{
		if  (ft_strncmp(str, lst->content, ft_strlen(str)) == 0)
		{
			return (lst->content + ft_strlen(str));
		}
		lst = lst->next;
	}
	return (NULL);
}

void	ft_free_table(char **table)
{
	int i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
	return ;
}

char	*triple_strjoin(char *s1, char *s2, char *s3)
{
	char *temp;
	char *ret;

	temp = ft_strjoin_libft(s1, s2);
	ret = ft_strjoin_libft(temp, s3);
	free(temp);
	return (ret);
}

char	*does_this_function_exist(t_a *a, int *i) //we want to dup and return the correct path.
{	//test on the current repo and on the path repo
	(void)i;
	char	**temp;
	char	*path;
	struct stat	buffer;
	int		j;
	char	*str;

	if (stat(a->raw[*i].str, &buffer) == 0)//first we try to execute the command locally
		return (ft_strdup(a->raw[*i].str));
	j = 0;
	path = return_str_from_env(a, "PATH=");
	temp = ft_split(path, ':');
	while (temp[j])
	{
		//write(1, "WWWWWWWWWW", 10);
		path = triple_strjoin(temp[j], "/", a->raw[*i].str);
		if (stat(path, &buffer) == 0)
		{
			str = ft_strdup(path);
			free(path);
			ft_free_table(temp);
			return (str);
		}
		free(path);
		j++;
	}
	ft_free_table(temp);
	return (NULL);
}

void	dup_fork_wait_execute(t_a *a, int *i)
{
	pid_t	pid;
	int		status;
	char	**argv;
	char	**aenv;
	char	*path;

	path = does_this_function_exist(a, i);
	//ft_putstr_fd(path, 1);
	if (path == NULL)
		add_env_or_command_not_found(a, i); 
	/*while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
		(*i)++; //activer cette partie pour permettre a georges d'avoir un env stable pour tester
	free(path);
	return ;*/

	argv = put_args_into_an_array(a, i);
	aenv = put_aenv_into_an_array(a, i);
	pid = fork();
	// checker si la fonction en chemin absolu ou relatif existe
	// si elle existe pas 
	if (pid == 0) //we are in the child if pid = 0
	{
		//write(1, "@@@@@@@@@@", 10);
		if (execve(path, argv, aenv) == -1) //a->raw[*i].str //exiter le chemin de av[0]
			exit (0); //remplace with strerrer & errno
		//ft_exit_clean(a, "Error:\nFork failed\n");
		//free(path);
		exit (0); //on kill syst // on doit exit clean ?
	}
	else if (pid < 0) //in case of fail
		ft_exit_clean(a, "Error:\nFork failed\n");
	else //parent, if the pid value is not 0
	{
		//write(1, "##########", 10);
		do
		{ 
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
		(*i)++;
	free (argv);
	free (aenv);
	free (path);
	return ;
}
