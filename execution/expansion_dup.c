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

void	expansion_dup(t_a *a, int *i)
{
	int	pipefd[2];

	replace_var_env_until_next_separator(a, i);

	//si on essaye d'ecrire sur un repertoire ou un fichier ou on a pas les droits, gerrer les erreurs
	// creation avec les bon droits 0644 pour un fichier

	//first of all I will try >

	a->v_fd = dup(1);
	(void)pipefd;
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

// TO MANAGE HERE
// dans un premier temps
	// > ecrit dans le fichier a droite , possible re rediriger le numero de sortie juste avant le > si il est colle
	// >> idem mais ecrit a la suite
	// < lit depuis le fichier a droite
// dans un second temps, en amont des guillemets
	// | les pipes
