#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# include <curses.h>
# include <term.h>
# include <termios.h>

# define SEPARATORS " '\"|;><"
# define MINISHELL_NAME "insert_title" //(╯°□°)╯︵ ┻━┻
# define PRINT_TOKENS 1
# define TERMCAPS 1
# define VERBOSE 0
# define DEBUG 0
# define LINE_CONTENT "echo pomme >line \n echo pomme"

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
	int			space_before; //1 si ' ' entre le token et celui d'avant, 0 sinon
}				t_raw;

typedef struct	s_a {
	int			ac;
	char		**av;
	char		**env;
	t_list		*lst_env;
	char		*line;
	char		*backup;
	char		*backup_backup;
	t_raw		*raw;
	int			len_raw;
	struct termios	trms;
	char		buff[5];
	int			fd;
	int			exit_status;
	int			i;
// Je pense qu'on va pouvoir nettoyer les fd_input et output de a->raw
	int			fd_input;
	int			fd_output;

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
	char		last_sep;
	int			lock_quote;

//$?
	int			dollar_question;
	int			there_is_dollar_question;

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
char	*ft_itoa(int n);

//print screens
void	ft_screen(t_a *a);
void	ft_init_screen(t_a *a);
void	ft_getcursorline(t_a *a);
void	ft_title(void);
void	ft_get_keyboard_input(t_a *a);
void	ft_appendexit(t_a *a);
void	ft_store_env_in_lst(t_a *a);

//signals
void	ft_affiche_controlesay(int useless);
void	ft_ctrlantislash(int useless);
void	ft_exit_from_branch(int useless);
void	ft_nothing_to_do(int useless);

//navigation
void	ft_save_hist(t_a *a, char *line);
void	ft_parsing(t_a *a);
int		get_next_line(int fd, char **line);
int		ft_strncmp(char *s1, char *s2, int n);
void	ft_init_termcap(t_a *a);
void	ft_exit_clean(t_a *a, char *str);
void	ft_print_string(t_a *a);

//redirections
void	ft_redirection(t_a *a);
void	ft_attributefd(t_a *a, int *i, int in_or_out);
void	ft_between_semicolon(t_a *a, int *i);
void	ft_fd_closing(t_a *a);
void	ft_backup_stdinandout(t_a *a);
void    ft_execution_sublevel(t_a *a);

//benjamin
void	set_backup_and_exit(t_a *a, char *str);
void	ft_execution(t_a *a);
void	add_env_or_command_not_found(t_a *a, int *i);
void	fork_wait_execute(t_a *a, int *i);
void	update_pwd(t_a *a, int *i);
int		ft_strlenn(char *str);
char	*free_null(char *s1);
int		free_int(char **line);

//benjamin parsing
void	replace_value_by_content(char *str);
void	replace_antislash_and_content_by_value(t_a *a);
void	replace_antislash_and_content_by_value2(int i, char *temp);
void	replace_and_shift(char *temp, int i, char c);
int		is_sep(char c, t_a *a);

int		calcul_k(t_a *a);
void	calcul_k_2(t_a *a, int i);
void	calcul_k_3(t_a *a, int *i, int *counter);
void	calcul_k_4(t_a *a);
void	calcul_k_5(t_a *a, int *i, int *counter);
void	calcul_k_6(t_a *a, int *i, int *counter);
void	calcul_init_backup(t_a *a, int *i, int *k);

void	init_split_and_backup(t_a *a, int *i, int *k);
void	increase_k_and_set_type_str_to_0(t_a *a, int *k);
void	skip_spaces(t_a *a, int *i, int *k);
void	manage_quotes(t_a *a, int *i, int *k, int *counter);
void	manage_simple_quote(t_a *a, int *i, int *k, int *counter);
void	manage_some_tokens(t_a *a, int *i, int *k);
void	manage_double_greater_than_sign(t_a *a, int *k);
void	manage_text(t_a *a, int *i, int *k, int *counter);

//benjamin execution
void	replace_var_env_until_next_separator(t_a *a, int *i);
void	try_to_replace_token_with_env(t_a *a, int j);
void	replace_me_if_you_find_me(t_a *a, int j, int k);
void	replace_dollar_question(t_a *a, char *temp, int j, int k);
void	join_before_env_after(t_a *a, int j, int k, char *src);
void	remove_token_from_content(t_a *a, int j, int k);
int		verification_content_env(char *str, t_a *a);

//listes
t_list	*ft_lstnew(char *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstclear(t_list **lst);
void	ft_lstdelone(t_list *lst);
int		ft_lstsize(t_list *lst);

#endif
