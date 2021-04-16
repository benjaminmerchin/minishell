#include "./includes/minishell.h"

void	ft_title(t_a *a)
{
	ft_putstr_fd("cristaline ", 1);
	ft_parsenv(a);
	ft_putstr_fd("> ", 1);
}

int		main(int ac, char **av, char **env)
{
	t_a		a;
	char	*term_type;
	int		ret;

	a.ac = ac;
	a.av = av;
	a.env = env;

	(void)ret;
	term_type = getenv("TERM");

	ft_initstruct(&a);
	ft_nav(&a);

	while(1)
	{
		ft_title(&a);
		ft_parsing(&a);
		ft_store_string(&a);
		ft_cleanstruct(&a);
	}
	return (0);
}
