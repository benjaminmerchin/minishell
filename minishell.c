#include "./includes/minishell.h"

void	ft_title(t_a *a)
{
	ft_putstr_fd(MINISHELL_NAME, 1);
	ft_putstr_fd(" ", 1);
	ft_parsenv(a);
	ft_putstr_fd("> ", 1);
}

void	ft_appendchar(t_a *a)
{
	char	*str;
	int		i;

	if (a->line[0] == 0)
	{
		a->line = malloc(sizeof(char) * 2);
		a->line[0] = a->buff[0];
		a->line[1] = 0;
		return ;
	}
	str = malloc(sizeof(char) * (ft_strlen(a->line) + 2));
	if (!str)
		//ft_exit_clean(a, "Error\nMalloc failed in appendchar\n");
		;
	i = -1;
	while (a->line[++i])
		str[i] = a->line[i];
	str[i] = a->buff[0];
	str[i + 1] = 0;
	free(a->line);
	a->line = str;
}

void	ft_store_env_in_lst(t_a *a)
{
	int i;
	t_list *lst;
	t_list *temp;
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

	while((ret = read(a->fd, a->buff, 4)))
	{
		a->buff[ret] = 0;
		if (ft_isprint(a->buff[0]))
		{
			ft_putchar_fd(a->buff[0], 1);
			ft_appendchar(a);
		}
			
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
	//ft_init_termcap(&a);
	while(1)
	{
		//ft_putstr_fd("\nMAIN\n", 1);
		ft_title(&a);
		if(TERMCAPS)
			ft_get_keyboard_input(&a);
		ft_parsing(&a);
		ft_split_sh(&a);
		ft_print_string(&a); //remove at the end
		ft_execution(&a); // execute the tokens
		ft_cleanstruct(&a); //verifier quon 
	}
	return (0);
}
