/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 23:21:54 by user42            #+#    #+#             */
/*   Updated: 2021/03/08 23:21:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_sep(char c, t_a *a)
{
	int i;

	i = 0;
	while (a->sep[i])
	{
		if (c == a->sep[i])
			return (1);
		i++;
	}
	return (0);
}

void	ft_split_sh(t_a *a)
{
	int		i;
	int		k;
	int		counter;

	i = 0;
	k = 0;
	a->raw = malloc(sizeof(*a->raw) * (1 + 1000)); //revenir dessus avec la meme fonction ft_split_sh mais sans malloc pour obtenir k
	if (!a->raw)
		return ;
	a->backup = a->line;
	a->raw[k].str = 0;
	a->raw[k].type = 0;
	while (a->line[i])
	{
		a->sep = a->backup_sep;
		if (a->line[i] == ' ')
		{
			while (is_sep(a->line[i + 1], a) && a->line[i] == ' ') //on avance sur ' ' et on stop au sep diff de ' ' ou au dernier ' '
				(a->line)++;
		} 
		//ici on se retrouve donc systematiquement sur le premier element
		if (a->line[i] == ' ' || !is_sep(a->line[i], a)) // si c'est pas un sep, le sep est un espace;
		{
			a->raw[k].type = ' ';
			if (a->line[0] == ' ')
				(a->line)++;
			if (a->line[0] == '\0') //si on fini par un espace on ne malloc rien
				break ;
			counter = 0;
			while (!is_sep(a->line[counter], a) && a->line[counter] != '\0')
				counter++;
			a->raw[k].str = malloc(sizeof(char) * (counter + 1));
			if (!a->raw[k].str)
				set_backup_and_exit(a, "Error\nMalloc Failed\n");
			while (counter > 0)
			{
				a->raw[k].str[i] = a->line[0];
				i++;
				counter--;
				(a->line)++;
			}
			a->raw[k].str[i] = 0;
			i = 0;
		}
		else if (ft_strlen(a->line) > 1 && a->line[0] == '>' && a->line[1] == '>')
		{
			a->raw[k].type = '#';
			a->raw[k].str = malloc(sizeof(char) * 3);
			a->raw[k].str[0] = '>';
			a->raw[k].str[1] = '>';
			a->raw[k].str[2] = 0;
			(a->line)++;
			(a->line)++;
		}
		else if (a->line[i] == '|' || a->line[i] == ';' || a->line[i] == '<' || a->line[i] == '>')
		{
			a->raw[k].type = a->line[i];
			a->raw[k].str = malloc(sizeof(char) * 2);
			a->raw[k].str[0] = a->line[i];
			a->raw[k].str[1] = 0;
			(a->line)++;
		}
		else if (a->line[i] == '"' || a->line[i] == '\'')
		{
			a->raw[k].type = a->line[i];
			if (a->line[i] == '"')
			{
				(a->line)++;
				counter = 0;
				while (a->line[counter] != '"' && a->line[counter] != '\0')
					counter++;
				if (a->line[counter] == '\0')
					set_backup_and_exit(a, "Error\nEnding quote missing\n");
				a->raw[k].str = malloc(sizeof(char) * (counter + 1));
				if (!a->raw[k].str)
					set_backup_and_exit(a, "Error\nMalloc Failed\n");
				while (counter > 0)
				{
					a->raw[k].str[i] = a->line[0];
					i++;
					counter--;
					(a->line)++;
				}
				a->raw[k].str[i] = 0;
				i = 0;
			}
			else //a->line[i] == '\''
			{
				(a->line)++;
				counter = 0;
				while (a->line[counter] != '\'' && a->line[counter] != '\0')
					counter++;
				if (a->line[counter] == '\0')
					set_backup_and_exit(a, "Error\nEnding quote missing\n");
				a->raw[k].str = malloc(sizeof(char) * (counter + 1));
				if (!a->raw[k].str)
					set_backup_and_exit(a, "Error\nMalloc Failed\n");
				while (counter > 0)
				{
					a->raw[k].str[i] = a->line[0];
					i++;
					counter--;
					(a->line)++;
				}
				a->raw[k].str[i] = 0;
				i = 0;
			}
			(a->line)++; //on depasse la deuxieme quote
		}
		else
		{
			write(1, "@@@@@@@@@@", 10);//erreur si on imprime des @
		}
		k++;
		a->raw[k].str = 0; //on termine toujours pas un 0 pour simplement free jusqu'au dernier 0
		a->raw[k].type = 0;
	}
	a->sep = a->backup_sep;
	a->line = a->backup;
}
