/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_wait_execute.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:00:55 by user42            #+#    #+#             */
/*   Updated: 2021/03/18 19:04:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expansion_dup(t_a *a, int *i)
{
	(void)i;
	(void)a;
	int save_stdin;

	save_stdin = dup(1);
	
}

/*

dup(1) = 3
open("test") = 4
dup2(4, 1)
close(4)
// execution des commandes
dup2(3, 1)
close(3)

*/