#include "../includes/minishell.h"

void	ft_init_screen(t_a *a)
{
	tputs(a->sc, 1, ft_putchar);
}

void		ft_getcursorline(t_a *a)
{
	char	buff[51];
	int		i;

	write(STDOUT_FILENO, "\033[6n", 4);
	i = read(STDOUT_FILENO, buff, 50);
	if (i <= 0)
		return ;
	buff[i] = 0;
	i = 0;
	while (buff[i] && buff[i] != '[')
		i++;
	while (buff[i] && !ft_isdigit(buff[i]))
		i++;
	a->current_line = ft_atoi(&buff[i]);
}

void	ft_do_we_jump(t_a *a)
{
	if ((ft_strlen(a->h[a->nav]) + a->len_head)
	/ a->column_term > a->line_term - a->current_line)
	{
		/*
		tputs(a->sf, 1, ft_putchar); //Je scrolle une ligne
		//tputs(a->up, 1, ft_putchar); //Je monte le curseur d'une ligne
		tputs(a->sc, 1, ft_putchar); //J'enregistre la nouvelle position
		a->current_line--;
		*/
	}
}

void	ft_screen(t_a *a)
{
	tputs(a->rc, 1, ft_putchar);
	ft_do_we_jump(a);
	tputs(a->cd, 1, ft_putchar); //je nettoie le bas de page
	ft_putstr_fd(a->h[a->nav], 1); //j'affiche la string dans son état actuel
	ft_putstr_fd("\n", 1);
}
