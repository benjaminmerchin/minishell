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
	a->raw = malloc(sizeof(*a->raw) * (1 + 1000)); //revenir dessus;
	if (!a->raw)
		return ;
	a->backup = a->line;
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
			counter = 0;
			while (!is_sep(a->line[counter], a) && a->line[counter] != '\0')
				counter++;
			a->raw[k].str = malloc(sizeof(char) * (counter + 1));
			if (!a->raw[k].str)
			{
				ft_putstr_fd("Error\nMalloc Failed\n", 2);
				a->line = a->backup;
				exit (1); // fonction d'exit a coder
			}
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
		else if (ft_strlen(a->line) > 2 && a->line[0] == '>' && a->line[1] == '>')
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
				{
					ft_putstr_fd("Error\nYour you are missing an ending quote\n", 2);
					a->line = a->backup;
					exit (1); // fonction d'exit a coder
				}
				a->raw[k].str = malloc(sizeof(char) * (counter + 1));
				if (!a->raw[k].str)
				{
					ft_putstr_fd("Error\nMalloc Failed\n", 2);
					a->line = a->backup;
					exit (1); // fonction d'exit a coder
				}
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
				{
					ft_putstr_fd("Error\nYour you are missing an ending quote\n", 2);
					a->line = a->backup;
					exit (1); // fonction d'exit a coder
				}
				a->raw[k].str = malloc(sizeof(char) * (counter + 1));
				if (!a->raw[k].str)
				{
					ft_putstr_fd("Error\nMalloc Failed\n", 2);
					a->line = a->backup;
					exit (1); // fonction d'exit a coder
				}
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
			write(1, "@@@@@@@@@@", 10);
		}
		k++;
	}
	a->raw[k].str = 0;
	a->sep = a->backup_sep;
	a->line = a->backup;
}

/*
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

int		is_sep_set(char c, t_a *a)
{
	int i;

	i = 0;
	while (a->sep[i])
	{
		if (c == a->sep[i])
		{
			if (a->vb_ap == 0)
			{
				if (a->sep[i] == '"')
					a->sep = "\"";
				if (a->sep[i] == '\'')
					a->sep = "'";
				a->vb_ap = 1;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

char	*store_my_token(t_a *a, int *i)
{
	int len_counter;
	char *tmp;
	int j;

	j = 0;
	len_counter = 0;
	while (!is_sep(a->line[*i + len_counter], a) && a->line[*i + len_counter] != '\0')
		len_counter++;
	tmp = malloc(sizeof(char) * (len_counter + 1));
	if (!tmp)
		return (NULL);
	//write(1, "#", 1);
	//ft_putnbr(len_counter);
	//ft_putchar('#');
	//ft_putstr(a->sep);
	//write(1, "#", 1);
	while (j < len_counter)
	{
		tmp[j] = a->line[*i];
		j++;
		(*i)++;
	}
	tmp[j] = 0;
	return (tmp);
}

void	ft_split_sh(t_a *a)
{
	int		i; // parcours le string
	int		k; // parcours le tableau de rangement des tokens
	char	*backup_line;

	backup_line = a->line;
	a->raw = malloc(sizeof(*a->raw) * (1 + 1000));
	if (!a->raw)
		return ;
	i = 0;
	k = 0;
	a->vb_ap = 0;
	while (a->line[i])
	{
		if (a->line[i] == ' ')
		{
			while (a->line[i + 1] == ' ')
				i++;
			if (is_sep(a->line[i + 1], a))
				i++;
		}
		if (!is_sep(a->line[0], a))
		{
			a->raw[k].type = ' ';
		}
		else
			a->raw[k].type = a->line[i];
		is_sep_set(a->line[i], a);
		if (a->line[i] == '|' || a->line[i] == ';')
		{
			a->raw[k].str = malloc(sizeof(char) * 2);
			a->raw[k].str[0] = a->line[0];
			a->raw[k].str[1] = 0;
			i++;
		}
		else
		{
			//ici on se retrouve au debut de ce qu'il faut mettre dans le contenu
			if (i != 0)
				i++;
			a->raw[k].str = store_my_token(a, &i);
			if ((a->line[i] == '\'' || a->line[i] == '"') && a->vb_ap == 1)
			{
				a->sep = " '\"|><;";
				a->vb_ap = 0;
				i++; //pour zapper le second ' ou "
				//write(1, "@", 1);
			}
		}
			//ft_putnbr(i);
		while (i > 0)
		{
			(a->line)++;
			i--;
		}
		k++;
	}
	a->raw[k].str = 0;
	a->line = backup_line;
}*/
