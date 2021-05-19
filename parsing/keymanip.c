/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymanip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:38:17 by user42            #+#    #+#             */
/*   Updated: 2021/04/25 18:38:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_init_screen(t_a *a)
{
	tputs(a->sc, 1, ft_putchar);
}

void		ft_getcursorline(t_a *a)
{
	char	buff[501];
	int		i;

	write(STDOUT_FILENO, "\033[6n", 4);
	i = read(STDOUT_FILENO, buff, 500);
	if (i < 0)
		return ;
	buff[i] = 0;
	i = 0;
	while (buff[i] && buff[i] != '[')
		i++;
	while (buff[i] && !ft_isdigit(buff[i]))
		i++;
	a->current_line = ft_atoi(&buff[i]);
}

void		ft_do_we_jump(t_a *a)
{
	int	nl;
	int fd;

	nl = (ft_strlen(a->h[a->nav]) + a->len_head + 2) / a->column_term;
	while (nl > a->line_term - a->current_line)
	{
		fd = open("./Termcaps", O_RDWR | O_APPEND | O_CREAT, 0644);
		ft_putstr_fd(ft_itoa(ft_strlen(a->h[a->nav])), fd);
		ft_putstr_fd(" <-ft_strlen(a->h[a->nav])\n", fd);
		ft_putstr_fd(ft_itoa(nl), fd);
		ft_putstr_fd(" <-nl\n", fd);
		ft_putstr_fd(ft_itoa(a->current_line), fd);
		ft_putstr_fd(" <-Current line\n", fd);
		ft_putstr_fd(ft_itoa(a->line_term), fd);
		ft_putstr_fd(" <-line term\n", fd);
		close(fd);

		tputs(a->sf, 1, ft_putchar);
		a->current_line = a->current_line - 1;
		tputs(tgoto(a->cm, 0, a->current_line - 1), 1, ft_putchar);
		tputs(a->cd, 1, ft_putchar);
		ft_title();
		tputs(a->sc, 1, ft_putchar);
	}
}

void	ft_screen(t_a *a)
{
	tputs(a->rc, 1, ft_putchar);
	ft_do_we_jump(a);
	tputs(a->cd, 1, ft_putchar);
	ft_putstr_fd(a->h[a->nav], 1);
}
