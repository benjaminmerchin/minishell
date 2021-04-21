#include "../includes/minishell.h"

void	ft_init_screen(t_a *a)
{
	tputs(a->sc, 1, ft_putchar);
}

void	ft_screen(t_a *a)
{
	tputs(a->cd, 1, ft_putchar);
	tputs(a->rc, 1, ft_putchar);
	tputs(a->cd, 1, ft_putchar);
	ft_putstr_fd(a->h[a->nav], 1);
	tputs(a->cd, 1, ft_putchar);
}