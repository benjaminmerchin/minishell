#include "../includes/minishell.h"

void	ft_raw_mode(t_a *a)
{

	tcgetattr(STDIN_FILENO, a->trms);
	a->trms->c_lflag &= ~(ICANON);
    a->trms->c_lflag &= ~(ECHO);
	if (tcsetattr(0, 0, a->trms) == -1)
        ft_exit_clean(a, "Error\nTermcap raw mode failed\n");

}

void	ft_init_tcap(t_a *a)
{
	int		i;

    if (a->term_type == NULL)
		ft_exit_clean(a, "Error\nTERM must be set (see 'env').\n");
    i = tgetent(NULL, a->term_type);
	if (i == -1 || i == 0)
        ft_exit_clean(a, "Error\nWe crashed the tgetent\n");
	if (setupterm(NULL, STDOUT_FILENO, NULL) == 0)
	{
		a->column_count = tgetnum("co");
		a->line_count = tgetnum("li");
		ft_raw_mode(a);
	}
}

void	ft_save_hist(t_a *a, char *line)
{
	if (line == 0)
		return ;
	ft_putstr_fd(line, 1);
	a->h[a->nline] = ft_strdup(line);
	a->nline++;
}
