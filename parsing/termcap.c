#include "../includes/minishell.h"

void	ft_raw_mode(t_a *a)
{
	struct termios z;

	tcgetattr(STDIN_FILENO, &a->trms);
	z = a->trms;
    z.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &z) == -1)
        ft_exit_clean(a, "Error\nTermcap raw mode failed\n");
}

void	ft_init_termcap(t_a *a)
{
	int		i;
	char	*term_type;

	term_type = getenv("TERM");
    if (term_type == NULL)
		ft_exit_clean(a, "Error\nTERM must be set (see 'env').\n");
	i = tgetent(NULL, term_type);
	if (i == -1 || i == 0)
        ft_exit_clean(a, "Error\nWe crashed the tgetent\n");
	a->column_term = tgetnum("co");
	a->line_term = tgetnum("li");
	//printf("Line of terminal : %d\nCol of terminal : %d\n", a->line_term, a->column_term);
	a->me = tgetstr("me", NULL);
	a->cm = tgetstr("cm", NULL);
	a->sc = tgetstr("sc", NULL);
	a->sf = tgetstr("sf", NULL);
	a->rc = tgetstr("rc", NULL);
	a->cd = tgetstr("cd", NULL);
	a->cl = tgetstr("cl", NULL);
	a->up = tgetstr("up", NULL);
	a->dw = tgetstr("do", NULL);
	//tputs(a->cl, 1, ft_putchar);
}

void	ft_save_hist(t_a *a, char *line)
{
	if (line == 0)
		return ;
	ft_putstr_fd(line, 1);
	a->h[a->nline] = ft_strdup(line);
	a->nline++;
}
