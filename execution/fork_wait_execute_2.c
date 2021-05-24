/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_wait_execute_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:00:55 by user42            #+#    #+#             */
/*   Updated: 2021/03/18 19:04:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_fork_wait_execute(char	**argv,	char **aenv, char *path)
{
	free (argv);
	free (aenv);
	free (path);
}

void	move_until_next_event(t_a *a, int *i)
{
	while (a->raw[*i].str != 0 && a->raw[*i].type
		!= '|' && a->raw[*i].type != ';')
		(*i)++;
}

void	fork_wait_execute_extension(t_a *a, int pid, int *status)
{
	waitpid(pid, status, WUNTRACED);
	while (!WIFEXITED(*status) && !WIFSIGNALED(*status))
		waitpid(pid, status, WUNTRACED);
	a->dollar_question = (*status % 255);
	if (g_fantaisie >= 127)
		a->dollar_question = g_fantaisie;
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
