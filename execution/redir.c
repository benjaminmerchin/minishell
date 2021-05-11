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
	a->raw[i + j].str = 0; //il y a un leak ici que je ne parviens pas à gérer
}

void	ft_redirection(t_a *a)
{
	int	k;
	int	fd;

	k = a->i;
	a->fd_input = dup(0);
	a->fd_output = dup(1);
	while (a->raw[k].type && a->raw[k].type != ';' && a->raw[k].type != '|')
	{
		if (a->raw[k].type == '<')
		{
			fd = open(a->raw[k + 1].str, O_RDONLY, 0644);
			if (fd <= 0)
				ft_exit_clean(a, "EXIT: Invalid source for < \n");
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
	close(a->fd_output);
	dup2(a->fd_input, 0);
	close(a->fd_input);
}

void	ft_attributefd(t_a *a, int *i, int in_or_out)
{
	/*in_or_out :
	0 pour une source <
	1 pour une destination >
	2 pour un "append à la fin" */
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
	/*
	else if (in_or_out == 1)
	{
		fd = open(a->raw[*i + 1].str, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (fd <= 0)
			ft_exit_clean(a, "Couldn't create file \n");
	}
	else
	{
		fd = open(a->raw[*i + 1].str, O_RDWR | O_APPEND | O_CREAT, 0644);
		if (fd <= 0)
			ft_exit_clean(a, "Couldn't create file \n");
	}*/
}

/*
void	ft_isbuiltin(t_a *a, int i)
{
	if (a->funcpos == -1 && (ft_strncmp(a->raw[i].str, "exit", 10) == 0 ||
	ft_strncmp(a->raw[i].str, "echo", 10) == 0 ||
	ft_strncmp(a->raw[i].str, "cd", 10) == 0 ||
	ft_strncmp(a->raw[i].str, "pwd", 10) == 0 ||
	ft_strncmp(a->raw[i].str, "export", 10) == 0 ||
	ft_strncmp(a->raw[i].str, "unset", 10) == 0 ||
	ft_strncmp(a->raw[i].str, "env", 10) == 0))
	{
		ft_putnbr_fd(i, 1);
		ft_putstr_fd(" <-Here, we found a builtin\n", 1);
		a->funcpos = i;
	}
	if (a->raw[i].type == '|' || a->raw[i].type == ';' )
		{
			ft_putnbr_fd(i, 1);
			ft_putstr_fd(" <-Here, got out of the builtin\n", 1);
			a->funcpos = -1;
		}
}

void	ft_funcpos(t_a *a, int i)
{
	if (a->raw[i].type == '|' || a->raw[i].type == ';' )
		{
			ft_putnbr_fd(i, 1);
			ft_putstr_fd(" <-Here, we clear funcpos\n", 1);
			a->funcpos = -1;
		}
	else if (i == 0 || a->raw[i - 1].type == '|' ||
	a->raw[i - 1].type == ';' )
		{
			ft_putnbr_fd(i, 1);
			ft_putstr_fd(" <-Here, we have a function\n", 1);
			a->funcpos = i;
		}
}*/