#include "../includes/minishell.h"

void	remove_token_from_list(t_a *a, int i)
{
	int j;

	j = 0;
	free(a->raw[i].str);
	while (a->raw[i + j + 1].type)
	{
		a->raw[i + j].type = a->raw[i + j + 1].type;
		a->raw[i + j].str = a->raw[i + j + 1].str;
		a->raw[i + j].space_before = a->raw[i + j + 1].space_before;
		j++;
	}
	(a->len_raw)--;
	a->raw[i + j].type = 0;
	a->raw[i + j].str = 0;
}

void	ft_redirection(t_a *a)
{
	int	k;
	int	fd;

	k = a->i;
	while (a->raw[k].type && a->raw[k].type != ';' && a->raw[k].type != '|')
	{
		if (a->raw[k].type == '<')
		{
			if (!a->raw[k + 1].type || a->raw[k + 1].type == ';')
			{
				a->dollar_question = 1;
				ft_putstr_fd("\033[033m", 1);
				ft_putstr_fd(MINISHELL_NAME, 1);
				ft_putstr_fd(" ", 1);
				ft_putstr_fd("Syntax error, unexpected newline or ;\n", 1);
				ft_putstr_fd("\033[0m", 1);
				while (a->raw[a->i].type)
					a->i++;
				a->i--;
				g_fantaisie = -25;
				return ;
			}
			fd = open(a->raw[k + 1].str, O_RDONLY, 0644);
			if (fd <= 0)
			{
				a->dollar_question = 1;
				ft_putstr_fd("\033[033m", 1);
				ft_putstr_fd(MINISHELL_NAME, 1);
				ft_putstr_fd(" ", 1);
				ft_putstr_fd(a->raw[k + 1].str, 1);
				ft_putstr_fd("': No such file or directory\n", 1);
				ft_putstr_fd("\033[0m", 1);
				while (a->raw[a->i].type)
					a->i++;
				g_fantaisie = -25;
				return ;
			}
			dup2(fd, 0);
			close(fd);
			remove_token_from_list(a, k);
			remove_token_from_list(a, k);
		}
		else if (a->raw[k].type == '>')
		{
			fd = open(a->raw[k + 1].str, O_RDWR | O_TRUNC | O_CREAT, 0644);
			if (fd <= 0)
				ft_exit_clean(a, "Couldn't create file \n");
			dup2(fd, 1);
			close(fd);
			remove_token_from_list(a, k);
			remove_token_from_list(a, k);
		}
		else if (a->raw[k].type == '#')
		{
			fd = open(a->raw[k + 1].str, O_RDWR | O_APPEND | O_CREAT, 0644);
			if (fd <= 0)
				ft_exit_clean(a, "Couldn't create file \n");
			dup2(fd, 1);
			close(fd);
			remove_token_from_list(a, k);
			remove_token_from_list(a, k);
		}
		else
			k++;
	}
}

void	ft_fd_closing(t_a *a)
{
	dup2(a->fd_output, 1);
	dup2(a->fd_input, 0);
}

void	ft_attributefd(t_a *a, int *i, int in_or_out)
{
	int		fd;
	
	if (in_or_out == 0)
	{
		fd = open(a->raw[*i + 1].str, O_RDONLY, 0644);
		if (fd < 0)
		{
			ft_putstr(MINISHELL_NAME);
			ft_putstr(a->raw[*i + 1].str);
			ft_putstr(": Aucun fichier ou dossier de ce type\n");
		}
		close(fd);
	}
}
