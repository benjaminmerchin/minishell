#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>

# include <curses.h>
# include <term.h>

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

//section pour la navigation fleche haut/bas
	int			nav;
	int			nline;
	char		**h;
//section utile pour split
	char 		*sep; //separateur sur lequel on parse
	char		last_sep;
}				t_a;

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(char *s);
int		ft_strlen(char *s);
void	ft_parsenv(t_a *a);
void	ft_split_sh(t_a *a);
//int		is_insep(char c, char *sep, t_a *a);
void	ft_initstruct(t_a *a);
void	ft_cleanstruct(t_a *a);
void	ft_putnbr_fd(int n, int fd);


//navigation
void	ft_save_hist(t_a *a, char *line);
void	ft_nav(t_a *a);

void	ft_parsing(t_a *a);
int		get_next_line(int fd, char **line);
char	*ft_joinofgnl(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
void 			ft_store_string(t_a *a);


#endif
