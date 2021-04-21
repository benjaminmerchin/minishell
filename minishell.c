#include "./includes/minishell.h"

void	ft_title(t_a *a)
{
	ft_putstr_fd(MINISHELL_NAME, 1);
	ft_putstr_fd(" ", 1);
	ft_parsenv(a); // output sur 1 tout le temps ?
	ft_putstr_fd("> ", 1);
}

void	ft_appendbuffer(t_a *a, int k)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * (ft_strlen(a->h[a->nav]) + k + 1));
	if (!str)
		ft_exit_clean(a, "Error\nMalloc failed in appendchar\n");
	i = 0;
	while (a->h[a->nav] && a->h[a->nav][i])
	{
		str[i] = a->h[a->nav][i];
		i++;
	}
	j = 0;
	while (j < k)
	{
		str[i] = a->buff[j];
		i++;
		j++;
	}
	str[i] = 0;
	if (a->h[a->nav])
		free(a->h[a->nav]);
	a->h[a->nav] = str;
}

void	ft_store_env_in_lst(t_a *a)
{
	int		i;
	t_list	*lst;
	t_list	*temp;
	char	*char_temp;
	
	i = 1;
	char_temp = ft_strdup(a->env[0]);
	lst = ft_lstnew(char_temp);
	while (a->env[i - 1] && a->env[i])
	{
		char_temp = ft_strdup(a->env[i]);
		temp = ft_lstnew(char_temp);
		ft_lstadd_back(&lst, temp);
		i++;
	}
	a->lst_env = lst;
}

void	ft_dedoublonne(t_a *a)
{
	if (a->nline < 2)
		return ;
	if (ft_strncmp(a->h[a->nline - 1], a->h[a->nline - 2],
	ft_strlen(a->h[a->nline - 1]) == 0))
	{
		if (a->h[a->nline - 1])
			free(a->h[a->nline - 1]);
		a->nline--;
		return ;
	}
}

void	ft_newline(t_a *a)
{
	if (a->line)
		free(a->line);
	a->line = ft_strdup(a->h[a->nav]); //j'envoie la ligne sur laquelle je suis dans le reste
	if ()
	if (a->nav == a->nline - 1)
	{
		ft_dedoublonne(a);
		return ;
	}
	else
	{
		if (a->h[a->nline - 1])
			free(a->h[a->nline - 1]);
		a->h[a->nline - 1] = ft_strdup(a->h[a->nav]);
		ft_dedoublonne(a);
	}
}

void	ft_updown(t_a *a)
{
	if (!a->h[0])
		return ;
	if (a->buff[0] == 27 && a->buff[1] == '[' && a->buff[2] == 'A' &&
	a->nav > 0)
	{
		ft_putstr_fd("\n^^^^ fleche haut\n", 1);
		a->nav--;
	}
	else if (a->buff[0] == 27 && a->buff[1] == '[' && a->buff[2] == 'B' &&
	a->nav < a->nline - 1)
	{
		ft_putstr_fd("\nvvvv fleche bas\n", 1);
		a->nav++;
	}

}

void	ft_get_keyboard_input(t_a *a)
{
	int 	ret;

	ft_putstr_fd("\n***On commence l'input***\n", 1);
	a->nline++;
	a->nav = a->nline - 1;
	ft_putnbr_fd(a->nline, 1);
	ft_putstr_fd("   ", 1);
	ft_putnbr_fd(a->nav, 1);
	ft_putstr_fd("\nnline   nav\n", 1);
	while((ret = read(a->fd, a->buff, 4)))
	{
		a->buff[ret] = 0;
		if (a->buff[0] == '\n')
		{
			ft_newline(a);
			int i = 0;
			ft_putstr_fd("\n***Voici h***\n", 1);
			while (a->h[i])
			{
				ft_putstr_fd(a->h[i], 1);
				ft_putstr_fd(" <- c'est dans hist\n", 1);
				i++;
			}
			ft_putnbr_fd(i ,1);
			ft_putstr_fd("\n****On sort de keyboard input après \\n****\n", 1);
			return ;
		}
		else if (a->buff[0] == 127 && ft_strlen(a->h[a->nav]) > 0)
			a->h[a->nav][ft_strlen(a->h[a->nav]) - 1] = 0;
		else if (a->buff[1] != 0 || !ft_isprint(a->buff[0]))
			ft_updown(a);
		else
			ft_appendbuffer(a, 1);
			//je n'ai pas encore trouvé de 
			//caractères imprimables de plus de 1 mais on ne sait jamais
		ft_putstr_fd("\n****a->h[a->nav]****\n", 1);
		ft_putstr_fd(a->h[a->nav], 1);
	}
}

int		main(int ac, char **av, char **env)
{
	t_a	a;

	a.ac = ac;
	a.av = av;
	a.env = env;

	ft_init_struct(&a);
	ft_store_env_in_lst(&a);
	if (TERMCAPS)
		ft_init_termcap(&a);
	while(1)
	{
		ft_title(&a);
		if(TERMCAPS)
			ft_get_keyboard_input(&a);
		else
			ft_parsing(&a);
		ft_split_sh(&a);
		ft_print_string(&a); //remove at the end
		ft_execution(&a); // execute the tokens
		ft_cleanstruct(&a); //verifier quon 
	}
	return (0);
}


/*	int	i;

	if (!a->line)
	{
		a->line = malloc(sizeof(char));
		a->line[0] = 0;
		ft_putstr_fd("\n****On sort avec un string vide****\n", 1);
		return ;
	}
	if (!a->line[0] || (a->h[a->nline] != 0 &&
	!ft_strncmp(a->line, a->h[a->nline], ft_strlen(a->line))))
	{
		ft_putstr_fd("\n****On n'append rien****\n", 1);
		return ;
	}
	ft_putstr_fd("\n++++\n", 1);
	if (a->h[a->nline] != 0)
		free(a->h[a->nline]);
	a->h[a->nline] = ft_strdup(a->line);
	a->nline ++;

	i = 0;
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("****on ralonge h***\n", 1);
	while (i < a->nline)
	{
		ft_putstr_fd(a->h[i], 1);
		ft_putstr_fd(" <- c'est dans hist\n", 1);
		i++;
	}*/