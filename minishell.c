#include "./includes/minishell.h"

void	ft_title(t_a *a)
{
	ft_putstr_fd("cristaline ", 1);
	ft_parsenv(a);
	ft_putstr_fd("> ", 1);
}

void	ft_get_keyboard_input(t_a *a)
{
	int ret;

	while((ret = read(a->fd, a->buff, 4)))
	{
		a->buff[ret] = 0;
		if (ft_isprint(a->buff[0]))
			ft_putchar_fd(a->buff[0], 1);
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
		ft_get_keyboard_input(&a);
		ft_title(&a);
		ft_parsing(&a);
		ft_split_sh(&a);
		ft_print_string(&a); //remove at the end
		ft_cleanstruct(&a);
	}
	return (0);
}
