#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>

# include <curses.h>
# include <term.h>
# include <termios.h>

# define SEPARATORS " '\"|;><"

typedef struct	s_raw {
	int			type;
	char		*str;
}				t_raw;

typedef struct	s_a {
	int			ac;
	char		**av;
	char		**env; //on y cherche le path PWD
	char		*line;
	char		*backup;
	t_raw		*raw;
	struct termios	*trms;

//Section termcap
	int			column_count;
	int			line_count;
	char		*term_type;
	char		*str_tcapped;

//section pour la navigation fleche haut/bas
	int			nav;
	int			nline;
	char		**h;
//section utile pour split
	char 		*sep; //a->sep = " '\"|;><";
	char		*backup_sep; //sep mais on y touche pas
	char		last_sep;

	int			vb_ap;
}				t_a;

void	ft_putchar_fd(char c, int fd);
int		ft_putchar(int c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putstr(char *s);
char	*ft_strdup(char *s);
int		ft_strlen(char *s);
void	ft_parsenv(t_a *a);
void	ft_split_sh(t_a *a);
void	ft_init_struct(t_a *a);
void	ft_cleanstruct(t_a *a);
void	ft_putnbr_fd(int n, int fd);
void	ft_putnbr(int n);


//navigation
void	ft_save_hist(t_a *a, char *line);

void	ft_parsing(t_a *a);
int		get_next_line(int fd, char **line);
char	*ft_joinofgnl(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);
void 	ft_store_string(t_a *a);

void	ft_init_tcap(t_a *a);
void	ft_exit_clean(t_a *a, char *str);



#endif
