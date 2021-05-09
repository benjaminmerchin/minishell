#include "../includes/minishell.h"

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
	
	ft_putstr_fd("This is the way : ", 1);
	ft_putstr_fd(a->raw[*i + 1].str, 1);
	ft_putstr_fd("\n", 1);
	if (in_or_out == 0)
	{
		fd = open(a->raw[*i + 1].str, O_RDONLY, 0644);
		if (fd < 0)
		{
			ft_putstr_fd("EXIT: Invalid source for < \n", 1);
		}
		else
		{
			ft_putnbr_fd(fd, 1);
			ft_putstr_fd(" <- We opened this fd\n", 1);
			a->raw[a->funcpos].fd_input = fd;
		}
	}
	else if (in_or_out == 1)
	{
		fd = open(a->raw[*i + 1].str, O_RDWR | O_TRUNC | O_CREAT, 0644);
		if (fd <= 0)
		{
			ft_putstr_fd("Couldn't create file \n", 1);
		}
		else
		{
			ft_putnbr_fd(fd, 1);
			ft_putstr_fd(" <- The file is created, and this is its fd\n", 1);
			a->raw[a->funcpos].fd_output = fd;
		}
	}
	else if (in_or_out == 2)
	{
		fd = open(a->raw[*i + 1].str, O_RDWR | O_APPEND | O_CREAT, 0644);
		if (fd <= 0)
		{
			ft_putstr_fd("Couldn't create file \n", 1);
		}
		else
		{
			ft_putnbr_fd(fd, 1);
			ft_putstr_fd(" <- The file is created, and this is its fd\n", 1);
			a->raw[a->funcpos].fd_output = fd;
		}
	}
}

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
}

void	expansion_dup_new(t_a *a, int *i)
{
	replace_var_env_until_next_separator(a, i);
	//je te fais totalement confiance sur ce coup

	if (a->raw[*i + 1].str != 0 && a->raw[*i].type == '<')
	{
		ft_putstr(">>>>>We found an < arrow<<<<\n");
		ft_attributefd(a, i, 0);
	}
	else if (a->raw[*i + 1].str != 0 && a->raw[*i].type == '>')
	{
		ft_putstr(">>>>>We found an > arrow<<<<\n");
		ft_attributefd(a, i, 1);
	}
	else if (a->raw[*i + 1].str != 0 && a->raw[*i].type == '#')
	{
		ft_putstr(">>>>>We found an >> arrow<<<<\n");
		ft_attributefd(a, i, 2);
	}
	//si on essaye d'ecrire sur un repertoire ou un fichier ou on a pas les droits, gerrer les erreurs
	// creation avec les bon droits 0644 pour un fichier
	// on peut detecter si 2>fichier.txt ou 2 > fichier.txt avec a->space_before

	//first of all I will try >
	//a->v_fd = dup(1);
}