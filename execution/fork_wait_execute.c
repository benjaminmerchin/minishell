/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_wait_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:00:55 by user42            #+#    #+#             */
/*   Updated: 2021/03/18 19:04:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**put_args_into_an_array(t_a *a, int *i)
{
	char	**table;
	int		j;

	j = 0;
	while (a->raw[*i + j].str != 0 && a->raw[*i + j].type != '|'
		&& a->raw[*i + j].type != ';')
		j++;
	table = malloc(sizeof(char *) * (j + 1));
	if (! table)
		ft_exit_clean(a, "Error\nMalloc Failed\n");
	j = 0;
	while (a->raw[*i + j].str != 0 && a->raw[*i + j].type != '|'
		&& a->raw[*i + j].type != ';')
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
	t_list	*lst;

	lst = a->lst_env;
	while (lst)
	{
		if (ft_strncmp(str, lst->content, ft_strlen(str)) == 0)
		{
			return (lst->content + ft_strlen(str));
		}
		lst = lst->next;
	}
	return (NULL);
}

void	ft_free_table(char **table)
{
	int	i;

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
	char	*temp;
	char	*ret;

	temp = ft_strjoin_libft(s1, s2);
	ret = ft_strjoin_libft(temp, s3);
	if (temp)
		free(temp);
	return (ret);
}

char	*does_this_function_exist(t_a *a, int *i, int j)
{
	char		**temp;
	char		*path;
	struct stat	buffer;
	char		*str;

	if (stat(a->raw[*i].str, &buffer) == 0)
		return (ft_strdup(a->raw[*i].str));
	path = return_str_from_env(a, "PATH=");
	temp = ft_split(path, ':');
	while (temp[j])
	{
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

void	fork_wait_execute(t_a *a, int *i)
{
	pid_t	pid;
	int		status;
	char	**argv;
	char	**aenv;
	char	*path;

	path = does_this_function_exist(a, i, 0);
	if (path == NULL)
		add_env_or_command_not_found(a, i);
	argv = put_args_into_an_array(a, i);
	aenv = put_aenv_into_an_array(a, i);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, argv, aenv) == -1)
			exit (a->dollar_question);
	}
	else if (pid < 0)
		ft_exit_clean(a, "Error:\nFork failed\n");
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
		a->dollar_question = (status % 255);
		if (g_fantaisie >= 127)
			a->dollar_question = g_fantaisie;
	}
	while (a->raw[*i].str != 0 && a->raw[*i].type
		!= '|' && a->raw[*i].type != ';')
		(*i)++;
	free (argv);
	free (aenv);
	free (path);
	return ;
}
