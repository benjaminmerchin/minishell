#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdio.h>

# include <curses.h>
# include <term.h>
# include <termios.h>

# define SEPARATORS " '\"|;><"
# define MINISHELL_NAME "grademe_100"
# define PRINT_TOKENS 1
# define TERMCAPS 0
# define VERBOSE 0

int		g_fantaisie;

typedef struct	s_struct
{
	char	buff[4 + 1];
	int		ret;
	int		curs;
}				t_struct;

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
	int			space_before; //1 si ' ' entre le token et celui d'avant, 0 sinon
}				t_raw;

typedef struct	s_a {
	int			ac;
	char		**av;
	char		**env;
	t_list		*lst_env;
	char		*line;
	char		*backup;
	t_raw		*raw;
	struct termios	trms;
	char		buff[5];
	int			fd;
	int			exit_status;

//Section termcap
	int			column_term;
	int			line_term;
	char		*me;
	char		*cm;
	char		*sc;
	char		*sf;
	char		*rc;
	char		*cd;	
	char		*cl;
	char		*up;
	char		*dw;

	char		*term_type;
	char		*str_tcapped;

//section pour la navigation fleche haut/bas
	int			nav;
	int			nline;
	char		**h;
//section bas de page
	int			current_line;
	int			len_head;

//section utile pour split
	char 		*sep; //a->sep = " '\"|;><";
	char		*backup_sep; //sep mais on y touche pas
	char		last_sep;

	int			v_fd; // -1 if everything is normal
	int			ret;
}				t_a;

int		main(int ac, char **av, char **env);

//En gros la libft
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
char	*ft_strjoin_libft(char *s1, char *s2);
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *nptr);

//print screens
void	ft_screen(t_a *a);
void	ft_init_screen(t_a *a);
void	ft_getcursorline(t_a *a);
void	ft_title(t_a *a);
void	ft_get_keyboard_input(t_a *a);
void	ft_appendexit(t_a *a);
void	ft_store_env_in_lst(t_a *a);

//signals
void	ft_stayinalive(int c);

//navigation
void	ft_save_hist(t_a *a, char *line);

void	ft_parsing(t_a *a);
int		get_next_line(int fd, char **line);
int		ft_strncmp(char *s1, char *s2, int n);

void	ft_init_termcap(t_a *a);
void	ft_exit_clean(t_a *a, char *str);
void	ft_print_string(t_a *a);


//benjamin
void	set_backup_and_exit(t_a *a, char *str);
void	ft_execution(t_a *a);
void	add_env_or_command_not_found(t_a *a, int *i);
void	fork_wait_execute(t_a *a, int *i);
void	update_pwd(t_a *a, int *i);
void	expansion_dup(t_a *a, int *i);
int		ft_strlenn(char *str);
char	*free_null(char *s1);
int		free_int(char **line);


//listes
t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstclear(t_list **lst);
void	ft_lstdelone(t_list *lst);
int		ft_lstsize(t_list *lst);

#endif
