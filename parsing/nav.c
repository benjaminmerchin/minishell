#include "../includes/minishell.h"

void	ft_nav(t_a *a)
{
	char	*term_type;
	int		ret;

	term_type = getenv("TERM");
    if (term_type == NULL)
        ft_putstr_fd("TERM must be set (see 'env').\n", 2);
    ret = tgetent(NULL, term_type);
	ft_putnbr_fd(ret, 1);
	ft_putstr_fd(term_type, 1);
	ft_putchar_fd('\n', 1);
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
