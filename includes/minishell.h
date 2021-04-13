#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct	s_a {
	int			ac;
	char		**av;
	char		**env;
	char		*line;
}				t_a;

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(char *s);
void	ft_parsenv(t_a *a);

void	ft_parsing(t_a *a);
int		get_next_line(int fd, char **line);
char	*ft_joinofgnl(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);



#endif
