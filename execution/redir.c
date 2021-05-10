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
		a->raw[i + j].fd_input = a->raw[i + j + 1].fd_input;
		a->raw[i + j].fd_output = a->raw[i + j + 1].fd_output;
		j++;
	}
	(a->len_raw)--;
	a->raw[i + j].str = 0; //il y a un leak ici que je ne parviens pas à gérer
}

void	ft_redirection(t_a *a)
{
	int	k;
	int	fd;

	k = a->i;
	a->fd_input = 0;
	a->fd_output = 0;
	while (a->raw[k].type && a->raw[k].type != ';' && a->raw[k].type != '|')
	{
		if (a->raw[k].type == '>')
		{
			fd = open(a->raw[k + 1].str, O_RDONLY, 0644);
			if (fd <= 0)
				ft_exit_clean(a, "EXIT: Invalid source for < \n");
			dup2(fd, 0);
			a->fd_input = 1;
			close(fd);
			ft_putstr(a->raw[k].str);
			remove_token_from_list(a, k);
			ft_putstr(a->raw[k].str);
			remove_token_from_list(a, k);
		}
		else if (a->raw[k].type == '<')
		{
			fd = open(a->raw[k + 1].str, O_RDWR | O_TRUNC | O_CREAT, 0644);
			if (fd <= 0)
				ft_exit_clean(a, "Couldn't create file \n");
			dup2(fd, 1);
			a->fd_output = 1;
			close(fd);
			ft_putstr(a->raw[k].str);
			remove_token_from_list(a, k);
			ft_putstr(a->raw[k].str);
			remove_token_from_list(a, k);
		}
		else if (a->raw[k].type == '#')
		{
			fd = open(a->raw[k + 1].str, O_RDWR | O_APPEND | O_CREAT, 0644);
			if (fd <= 0)
				ft_exit_clean(a, "Couldn't create file \n");
			dup2(fd, 1);
			a->fd_output = 1;
			close(fd);
			ft_putstr(a->raw[k].str);
			remove_token_from_list(a, k);
			ft_putstr(a->raw[k].str);
			remove_token_from_list(a, k);
		}
		else
			k++;
	}
}


/*void	expansion_dup(t_a *a, int *i)
{
	int	pipefd[2];
	(void)pipefd;

	ft_putstr("\nYou shouldn't be there\n");
	replace_var_env_until_next_separator(a, i);

	if (a->raw[*i].type == '>') //just an example to prove that the function can remove token
		remove_token_from_list(a, *i); //basically move all tokens one i closer

	//si on essaye d'ecrire sur un repertoire ou un fichier ou on a pas les droits, gerrer les erreurs
	// creation avec les bon droits 0644 pour un fichier
	// on peut detecter si 2>fichier.txt ou 2 > fichier.txt avec a->space_before

	//first of all I will try >

	a->v_fd = dup(1);
}*/

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