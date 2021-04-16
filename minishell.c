#include "./includes/minishell.h"

void	ft_title(t_a *a)
{
	ft_putstr_fd("cristaline ", 1);
	ft_parsenv(a);
	ft_putstr_fd("> ", 1);
}

void	ft_get_keyboard_input(t_a *a)
{
	
}

int		main(int ac, char **av, char **env)
{
	t_a		a;

	a.ac = ac;
	a.av = av;
	a.env = env;

	ft_init_struct(&a);
	ft_init_tcap(&a);
	while(1)
	{
		ft_get_keyboard_input(&a);
		ft_title(&a);
		ft_parsing(&a);
		ft_store_string(&a);
		ft_cleanstruct(&a);
	}
	return (0);
}
