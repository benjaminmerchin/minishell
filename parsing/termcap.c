#include "../includes/minishell.h"

void	ft_init_tcap(t_a *a)
{
	struct termios s_termios;


	tcgetattr(STDIN_FILENO, origin);
	s_termios.c_lflag &= ~(ICANON);
    s_termios.c_lflag &= ~(ECHO);
	if (tcsetattr(0, 0, &s_termios) == -1)
        return ;

}

void	ft_getinput(t_a *a)
{
	int		ent;

	a->term_type = getenv("TERM");
    if (a->term_type == NULL)
        ft_putstr_fd("TERM must be set (see 'env').\n", 2);
    ent = tgetent(NULL, a->term_type);
	if (ent == -1 || ent == 0)
    {
        ft_putstr_fd("We crashed the tgetent\n", 1);
        return ;
    }
	if (setupterm(NULL, STDOUT_FILENO, NULL) == 0)
	{
		a->column_count = tgetnum("co");
		a->line_count = tgetnum("li");
		ft_init_tcap(a);
	}
	(void)a;
}

void	ft_save_hist(t_a *a, char *line)
{
	if (line == 0)
		return ;
	ft_putstr_fd(line, 1);
	a->h[a->nline] = ft_strdup(line);
	a->nline++;
}
