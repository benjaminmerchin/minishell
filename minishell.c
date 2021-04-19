#include "./includes/minishell.h"

void	ft_title(t_a *a)
{
	ft_putstr_fd(MINISHELL_NAME, 1);
	ft_putstr_fd(" ", 1);
	ft_parsenv(a);
	ft_putstr_fd("> ", 1);
}

void	ft_appendbuffer(t_a *a, int k)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * (ft_strlen(a->line) + k + 1));
	if (!str)
		ft_exit_clean(a, "Error\nMalloc failed in appendchar\n");
	i = 0;
	while (a->line && a->line[i])
	{
		str[i] = a->line[i];
		i++;
	}
	j = 0;
	while (j < k)
	{
		str[i] = a->buff[j];
		i++;
		j++;
	}
	ft_putstr_fd("La line est propre?\n", 1);
	ft_putstr_fd(a->line, 1);
	ft_putstr_fd("\n", 1);
	str[i] = 0;
	ft_putstr_fd(str, 1);
	free(a->line);
	a->line = str;
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

void	ft_get_keyboard_input(t_a *a)
{
	int ret;
	//int	i;

	while((ret = read(a->fd, a->buff, 4)))
	{
		a->buff[ret] = 0;
		if (a->buff[0] == '\n')
		{
			//faire une fonction append à h, et les free
			return ;
		}
		if (a->buff[1] != 0)
			ft_putchar_fd(a->buff[1], 1);
		else
			ft_appendbuffer(a, 1);
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
		ft_putstr_fd("On get les inputs ?\n", 1);
		ft_putstr_fd(a.line, 1);
		if(TERMCAPS == 0)
			ft_parsing(&a);
		ft_split_sh(&a);
		ft_print_string(&a); //remove at the end
		ft_execution(&a); // execute the tokens
		ft_cleanstruct(&a); //verifier quon 
	}
	return (0);
}


/*

	int ret;
	int	i;

	while((ret = read(a->fd, a->buff, 4)))
	{
		i = 0;
		while (ft_isprint(a->buff[i]) || a->buff[i] == '\n')
		{
			if (a->buff[i] == '\n')
			{
				ft_putstr_fd("---ON A UN NEWLINE---\n", 1);
				ft_appendbuffer(a, i);
				return ;
			}
		i++;
		}
		a->buff[i] = 0;
		ft_appendbuffer(a, i);
	}

*/