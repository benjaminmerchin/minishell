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
# define MINISHELL_NAME "twentyfifth"
# define TERMCAPS 1

typedef struct	s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

typedef struct	s_raw {
	int			type;
	char		*str;
	int			fd_input;
	int			fd_output;
}				t_raw;

typedef struct	s_a {
	int			ac;
	char		**av;
	char		**env; //on y cherche le path PWD
	t_list		*lst_env;
	char		*line;
	char		*backup;
	t_raw		*raw;
	struct termios	trms;
	char		buff[5];
	int			fd;

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
int		ft_isprint(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);

//navigation
void	ft_save_hist(t_a *a, char *line);

void	ft_parsing(t_a *a);
int		get_next_line(int fd, char **line);
char	*ft_joinofgnl(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, int n);

void	ft_init_termcap(t_a *a);
void	ft_exit_clean(t_a *a, char *str);
void	ft_print_string(t_a *a);




//benjamin
void	set_backup_and_exit(t_a *a, char *str);
void	ft_execution(t_a *a);

//listes
t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstclear(t_list **lst);
void	ft_lstdelone(t_list *lst);
int	ft_lstsize(t_list *lst);

#endif
