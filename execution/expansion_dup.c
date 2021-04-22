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

int		verification_content_env(char *str)
{
	int j;
	int error;

	j = 0;
	error = 0;
	while (str[j] != '$' && str[j] != '\0' && (ft_isalnum(str[j]) || str[j] == '_'))
	{
		if ((j > 0 && !(ft_isalnum(str[j]) || str[j] == '_'))
		|| (j == 0 && !(ft_isalpha(str[j]) || str[j] == '_')))
		{
			error = 1;
			break ;
		}
		j++;
	}
	j++;
	if (j == 0 || error == 1)
		return(-1);
	return (j);
}

void	remove_token_from_content(t_a *a, int j, int k)
{
	(void)k;
	int m;
	//on souhaite malloc sur le nouveau content la longueur avant le $ et celle apres la fin du dernier ft_isalnum
	char *temp;
	m = 0;
	/*write(1, "@@@@@@@@@@", 10);
	ft_putnbr(ft_strlen(a->raw[j].str) - a->ret + 1);
	ft_putstr("    ");
	ft_putnbr(a->ret);
	ft_putstr("    ");
	ft_putnbr(j);
	ft_putstr("    ");
	ft_putnbr(k);
	ft_putstr("    ");*/
	temp = malloc(sizeof(char) * (ft_strlen(a->raw[j].str) - a->ret + 1));
	while (m < k)
	{
		temp[m] = a->raw[j].str[m];
		m++;
	}
	while (a->raw[j].str[m + a->ret])
	{
		temp[m] = a->raw[j].str[m + a->ret];
		m++;
	}
	temp[m] = '\0';
	free(a->raw[j].str);
	a->raw[j].str = temp;
}

void	join_before_env_after(t_a *a, int j, int k, char *src)
{
	int m;
	int n;
	int o;
	char *temp;

	m = -1;
	n = 0;
	temp = malloc(sizeof(char) * (ft_strlen(a->raw[j].str) - a->ret + 1 + ft_strlen(src)));
	while (++m < k)
		temp[m] = a->raw[j].str[m];
	o = m;
	while (n < ft_strlen(src))
		temp[m++] = src[n++];
	while (a->raw[j].str[o + a->ret])
	{
		temp[m] = a->raw[j].str[o + a->ret];
		m++;
		o++;
	}
	temp[m] = '\0';
	free(a->raw[j].str);
	a->raw[j].str = temp;
}

void	replace_me_if_you_find_me(t_a *a, int j, int k)
{
	t_list	*lst;
	int		l;

	k++; //to pass the $
	lst = a->lst_env;
	while(lst)
	{
		l = 0;
		while (lst->content[l] == a->raw[j].str[l + k] && a->raw[j].str[l + k] && lst->content[l] && l < a->ret)
			l++;
		//ft_putnbr(l);
		//if (l > 2)
		//	write(1, "MMMMMMMMMM", 10);
		if (lst->content[l] == '=' && (a->raw[j].str[l + k] == '\0' || (ft_isprint(a->raw[j].str[l + k]) && (!ft_isalnum(a->raw[j].str[l + k]) &&  a->raw[j].str[l + k] != '_'))) && l > 0)
		{
			join_before_env_after(a, j, k - 1, lst->content + l + 1);
			return ;
		}
		lst = lst->next;
	}
	remove_token_from_content(a, j, k - 1);
}

void	try_to_replace_token_with_env(t_a *a, int j)
{
	(void)j;
	(void)a;
	int k;

	k = 0;
	while (a->raw[j].str[k])
	{
		if (a->raw[j].str[k] == '$' && a->raw[j].str[k + 1] != '\0')
		{
			a->ret = verification_content_env(a->raw[j].str + k + 1); // renvoie la longueur positive si on a un str valide
			if (a->ret > 0)
				replace_me_if_you_find_me(a, j, k); //remplace par du vide si il ne trouve pas
			else
				remove_token_from_content(a, j, k);
		}
		k++;
	}
}

void	replace_var_env_until_next_separator(t_a *a, int *i)
{
	int j;

	j = *i;
	while (a->raw[j].str != 0 && a->raw[j].type != '|' && a->raw[j].type != ';')
	{
		if (a->raw[j].type != '\'')
			try_to_replace_token_with_env(a, j);
		j++;
	}
}

void	expansion_dup(t_a *a, int *i)
{
	(void)i;
	(void)a;
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
// quand j'ai le temps
	// $env $replace
