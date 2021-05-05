#include "../includes/minishell.h"

void	pipemanager(t_a *a, int input, int output)
{
	int	fd[2];

	if (pipe(fd) == -1)
		ft_exit_clean(a, "Pipe problem");
	a->raw[input].fd_input = fd[0];
	a->raw[output].fd_output = fd[1];
}

