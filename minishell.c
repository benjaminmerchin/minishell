#include "./includes/minishell.h"

void	ft_title(t_a *a)
{
	ft_putstr_fd("cristaline ", 1);
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
	t_a		a;

	a.ac = ac;
	a.av = av;
	a.env = env;

	ft_init_struct(&a);
	ft_init_termcap(&a);
	while(1)
	{
		ft_putstr_fd("\nMAIN\n", 1);
		ft_title(&a);
		ft_get_keyboard_input(&a);
		//ft_parsing(&a);
		ft_split_sh(&a);
		ft_print_string(&a); //remove at the end
		ft_cleanstruct(&a); //verifier quon 
	}
	return (0);
}
