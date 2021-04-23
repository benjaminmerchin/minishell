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

void	replace_and_shift(char *temp, int i, char c)
{
	temp[i] = c;
	i++;
	while (temp[i])
	{
		temp[i] = temp[i + 1];
		i++;
	}
}

void	replace_antislash_and_content_by_value(t_a *a)
{ //the idea is to replace temporarily for example ' by an int value of 2 if we don't want to consider it as a '
	int i;
	char *temp;

	i = 0;
	temp = a->line;
	while (temp[i])
	{
		if (temp[i] == '\\')
		{
			if (temp[i + 1] == ' ')
				replace_and_shift(temp, i, 1);
			else if (temp[i + 1] == '\'')
				replace_and_shift(temp, i, 2);
			else if (temp[i + 1] == '\\')
				replace_and_shift(temp, i, 3);
			else if (temp[i + 1] == '"')
				replace_and_shift(temp, i, 4);
			else if (temp[i + 1] == '|')
				replace_and_shift(temp, i, 5);
			else if (temp[i + 1] == ';')
				replace_and_shift(temp, i, 6);
			else if (temp[i + 1] == '<')
				replace_and_shift(temp, i, 7);
			else if (temp[i + 1] == '>')
				replace_and_shift(temp, i, 8);
			else if (temp[i + 1] == '\0')
				replace_and_shift(temp, i, '\\');
		}
		i++;
	}
}

/*
** ' ' = 1
** ''' = 2
** '\' = 3
** '"' = 4
** '|' = 5
** ';' = 6
** '<' = 7
** '>' = 8
*/

void	replace_value_by_content(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 1)
			str[i] = ' ';
		else if (str[i] == 2)
			str[i] = '\'';
		else if (str[i] == 3)
			str[i] = '\\';
		else if (str[i] == 4)
			str[i] = '"';
		else if (str[i] == 5)
			str[i] = '|';
		else if (str[i] == 6)
			str[i] = ';';
		else if (str[i] == 7)
			str[i] = '<';
		else if (str[i] == 8)
			str[i] = '>';
		i++;
	}
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
		ft_exit_clean(a, "Error\nMalloc Failed\n");
	replace_antislash_and_content_by_value(a);
	a->backup = a->line;
	a->raw[k].str = 0;
	a->raw[k].type = 0;
	a->raw[k].space_before = 0;
	while (a->line[i])
	{
		a->raw[k].space_before = 0;
		if (a->line[i] == ' ')
		{
			a->raw[k].space_before = 1;
			while (is_sep(a->line[i + 1], a) && a->line[i] == ' ') //on avance sur ' ' et on stop au sep diff de ' ' ou au dernier ' '
				(a->line)++;
		} 
		//ici on se retrouve donc systematiquement sur le premier element
		if (a->line[i] == ' ' || !is_sep(a->line[i], a)) // si c'est pas un sep, le sep est un espace;
		{
			a->raw[k].type = ' ';
			if (a->line[0] == ' ')
			{
				(a->line)++;
				a->raw[k].space_before = 1;
			}
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
			if (!a->raw[k].str)
				set_backup_and_exit(a, "Error\nMalloc Failed\n");
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
			if (!a->raw[k].str)
				set_backup_and_exit(a, "Error\nMalloc Failed\n");
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
			write(1, "@@@@@@@@@@", 10);//erreur si on imprime des @
		replace_value_by_content(a->raw[k].str);
		k++;
		a->raw[k].str = 0; //on termine toujours pas un 0 pour simplement free jusqu'au dernier 0
		a->raw[k].type = 0;
	}
	a->line = a->backup;
}
