#include "./includes/minishell.h"

void	ft_title(void)
{
	char	pwdname[1024];

	ft_putstr_fd("\033[035m", 1);
	ft_putstr_fd(MINISHELL_NAME, 1);
	ft_putstr_fd("\033[036m ", 1);
	if (getcwd(pwdname, sizeof(pwdname)) == NULL)
		return ;
	ft_putstr_fd(pwdname, 1);
	ft_putstr_fd("> \033[0m", 1);
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
	ft_strlen(a->h[a->nline - 1])) == 0)
	{
		if (VERBOSE)
			ft_putstr_fd("\nOn a un doublon sur les deux derniers\n", 1);
		if (a->h[a->nline - 1])
		{
			a->h[a->nline - 1][0] = 0;
			free(a->h[a->nline - 1]);
		}
		a->nline--;
		return ;
	}
}

void	ft_newline(t_a *a)
{
	if (a->line && !DEBUG)
		free(a->line);
	a->line = ft_strdup(a->h[a->nav]); //j'envoie la ligne sur laquelle je suis dans le reste
	if (!a->h[a->nav][0])
	{
		if (a->h[a->nline - 1])
			free(a->h[a->nline - 1]);
		a->nline--;
		return ;
	}
	else if (a->nav == a->nline - 1)
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
		//ft_putstr_fd("\n^^^^ fleche haut\n", 1);
		a->nav--;
	}
	else if (a->buff[0] == 27 && a->buff[1] == '[' && a->buff[2] == 'B' &&
	a->nav < a->nline - 1)
	{
		//ft_putstr_fd("\nvvvv fleche bas\n", 1);
		a->nav++;
	}

}

void	ft_appendexit(t_a *a)
{
	if (a->h[a->nav])
		free(a->h[a->nav]);
	if (a->buff[0] == 4)
		a->h[a->nav] = ft_strdup("exit");
	a->buff[0] = '\n';
	ft_screen(a);
}

void	ft_get_keyboard_input(t_a *a)
{
	int 	ret;

	a->nline++;
	a->nav = a->nline - 1;
	a->h[a->nav] = malloc(sizeof(char));
	a->h[a->nav][0] = 0;
	ft_init_screen(a);
	ft_getcursorline(a);
	while((ret = read(a->fd, a->buff, 4)))
	{
		a->buff[ret] = 0;
		if (a->buff[0] == 4)
			ft_appendexit(a);
		if (a->buff[0] == '\n')
		{
			ft_newline(a);
			if (VERBOSE)
				ft_putstr_fd("****On sort de keyboard input après \\n****\n", 1);
			else
				ft_putstr_fd("\n", 1);
			return ;
		}
		else if (a->buff[0] == 127 && ft_strlen(a->h[a->nav]) > 0)
			a->h[a->nav][ft_strlen(a->h[a->nav]) - 1] = 0;
		else if (a->buff[0] == 27 && a->buff[1] == '[')
			ft_updown(a);
		else
			ft_appendbuffer(a, ft_strlen(a->buff));
		ft_screen(a);
	}
}

int		main(int ac, char **av, char **env)
{
	t_a		a;

	a.ac = ac;
	a.av = av;
	a.env = env;
	g_fantaisie = 1;
	ft_init_struct(&a);
	ft_store_env_in_lst(&a);
	if (TERMCAPS)
		ft_init_termcap(&a);
	signal(SIGINT, ft_stayinalive);
	signal(SIGQUIT, ft_ctrlantislash);
	while (1)
	{
		ft_title();
		if(TERMCAPS)
			ft_get_keyboard_input(&a);
		else
			ft_parsing(&a);
		ft_split_sh(&a);
		ft_print_string(&a); //remove at the end
		a.i = 0;
		temporary_set_all_input_to_0_and_output_to_1(&a);
		ft_execution(&a); // execute the tokens
		ft_cleanstruct(&a); //verifier quon
		if (DEBUG)
			exit (0);
	}
	return (0);
}
