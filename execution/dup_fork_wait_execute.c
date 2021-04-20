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

//mettre les env en tab
//utiliser waitpid

void	dup_fork_wait_execute(t_a *a, int *i)
{
	pid_t	pid;
	int		status;
	char	**argv;
	char	**aenv;
	//char	*path;

	add_env_or_command_not_found(a, i); //pour georges
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
		(*i)++;
	return ;

	pid = fork();
	argv = put_args_into_an_array(a, i);
	aenv = put_aenv_into_an_array(a, i);
	//path = does_this_function_exist(a, i);
	// checker si la fonction en chemin absolu ou relatif existe
	// si elle existe pas 
	if (pid == 0)
	{
		write(1, "@@@@@@@@@@", 10);
		if (execve(a->av[0], argv, aenv) == -1) //a->raw[*i].str //exiter le chemin de av[0]
			perror("temporaire"); //remplace perror with strerrer & errno
		//ft_exit_clean(a, "Error:\nFork failed\n");
		add_env_or_command_not_found(a, i);	//80%
	}
	else if (pid < 0)
		ft_exit_clean(a, "Error:\nFork failed\n");
	else
	{
		write(1, "##########", 10);
		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	while (a->raw[*i].str != 0 && a->raw[*i].type != '|' && a->raw[*i].type != ';')
		(*i)++;
	free (argv);
	free (aenv);
	return ;
}

/*int lsh_launch(char **args)
{
	pid_t pid;
	int status;

 	 pid = fork();
  	if (pid == 0) 
  	{
    // Child process
   		if (execvp(args[0], args) == -1) 
		{
    		perror("lsh");
		}
    	exit(EXIT_FAILURE);
 	} 
  	else if (pid < 0)
	{
    // Error forking
  		perror("lsh");
 	} 
	else 
	{
    // Parent process
		do 
		{
			waitpid(pid, &status, WUNTRACED);
		}
		while (!WIFEXITED(status) && !WIFSIGNALED(status));
  	}
  	return 1;
}*/
