#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct	s_raw {
	int			type;
	char		*str;
}				t_raw;

typedef struct	s_a {
	int			ac;
	char		**av;
	char		**env; //on y cherche le path PWD
	char		*line;
	t_raw		*raw;

//section utile pour split
	char 		*sep; //separateur sur lequel on parse
	char		last_sep;
}				t_a;

void	ft_putchar_fd(char c, int fd);
void	ft_putchar(char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr(char *s);
int		ft_strlen(char *s);
void	ft_parsenv(t_a *a);
void	ft_split_sh(t_a *a);
//int		is_insep(char c, char *sep, t_a *a);
void	ft_initstruct(t_a *a);
void	ft_cleanstruct(t_a *a);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr(int n);




void	ft_parsing(t_a *a);
int		get_next_line(int fd, char **line);
char	*ft_joinofgnl(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
void 			ft_store_string(t_a *a);


#endif
