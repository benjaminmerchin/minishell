#ifndef MINISHELL_H
# define MNISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_a {
	int			ac;
	char		**av;
	char		**env;
}				t_a;

void	ft_putchar_fd(char c, int fd);
int		ft_strlen(char *s);




#endif
