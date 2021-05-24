/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtaverne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:55:42 by gtaverne          #+#    #+#             */
/*   Updated: 2021/05/23 18:55:45 by gtaverne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_updown(t_a *a)
{
	if (!a->h[0])
		return ;
	if (a->buff[0] == 27 && a->buff[1] == '[' && a->buff[2] == 'A'
		&& a->nav > 0)
		a->nav--;
	else if (a->buff[0] == 27 && a->buff[1] == '[' && a->buff[2] == 'B'
		&& a->nav < a->nline - 1)
		a->nav++;
	if (ft_strlen(a->h[a->nav]) > 0)
		signal(SIGINT, ft_ctrlc_in_buffer);
	else
		signal(SIGINT, ft_affiche_controlesay);
}

void	ft_appendexit(t_a *a)
{
	if (a->h[a->nav])
		free(a->h[a->nav]);
	if (a->buff[0] == 4)
		a->h[a->nav] = ft_strdup("exit");
	a->buff[0] = '\n';
	ft_screen(a);
}

void	init_keyboard_input(t_a *a)
{
	a->nline++;
	a->nav = a->nline - 1;
	a->h[a->nav] = malloc(sizeof(char));
	a->h[a->nav][0] = 0;
	a->buff[0] = 0;
	ft_init_screen(a);
	ft_getcursorline(a);
}
