/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:00:55 by user42            #+#    #+#             */
/*   Updated: 2021/03/18 19:04:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ft_get_keyboard_input_p1(t_a *a)
{
	int	ret;

	ret = read(0, a->buff, 4);
	if (ret <= 0)
		return ;
	a->buff[ret] = 0;
	if (g_fantaisie == -30)
	{
		g_fantaisie = 1;
		a->dollar_question = 1;
		a->nav = a->nline - 1;
		if (a->h[a->nav])
			free (a->h[a->nav]);
		a->h[a->nav] = malloc(sizeof(char));
		a->h[a->nav][0] = 0;
	}
	if (ft_strlen(a->h[a->nav]) > 0)
		signal(SIGINT, ft_ctrlc_in_buffer);
	else
		signal(SIGINT, ft_affiche_controlesay);
	if (a->buff[0] == 4 && ft_strlen(a->h[a->nav]) == 0)
		ft_appendexit(a);
}

void	ft_get_keyboard_input(t_a *a)
{
	init_keyboard_input(a);
	while (1)
	{
		ft_get_keyboard_input_p1(a);
		if (a->buff[0] == '\n')
		{
			ft_newline(a);
			ft_putstr_fd("\n", 1);
			return ;
		}
		else if (a->buff[0] == 127)
		{
			if (ft_strlen(a->h[a->nav]) > 0)
				a->h[a->nav][ft_strlen(a->h[a->nav]) - 1] = 0;
		}
		else if (a->buff[0] == 27 && a->buff[1] == '[')
			ft_updown(a);
		else if (a->buff[0] != 4)
			ft_appendbuffer(a, ft_strlen(a->buff));
		ft_screen(a);
	}
}

void	init_main(t_a *a, int ac, char **av, char **env)
{
	a->ac = ac;
	a->av = av;
	a->env = env;
	g_fantaisie = 1;
	ft_init_struct(a);
	ft_store_env_in_lst(a);
	if (TERMCAPS)
		ft_init_termcap(a);
}

int	main(int ac, char **av, char **env)
{
	t_a	a;

	init_main(&a, ac, av, env);
	while (1)
	{
		ft_title();
		if (TERMCAPS)
		{	
			ft_raw_mode(&a);
			signal(SIGINT, ft_affiche_controlesay);
			signal(SIGQUIT, ft_nothing_to_do);
			ft_get_keyboard_input(&a);
			ft_cleantermcaps(&a);
		}
		else
			ft_parsing(&a);
		ft_split_sh(&a);
		ft_print_string(&a);
		ft_backup_stdinandout(&a);
		ft_execution(&a);
		ft_cleanstruct(&a);
		if (DEBUG)
			exit(0);
	}
	return (0);
}
