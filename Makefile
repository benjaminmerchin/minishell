NAME	=	minishell
CC		=	clang
HEADER	=	includes/minishell.h
OBJDIR	=	object
SRC		=	minishell.c \
			\
			utils/utils.c utils/gnl_utils.c utils/gnl.c utils/libft_lst.c \
			utils/utils2.c utils/clean_exit.c utils/libft.c utils/libft_split.c\
			\
			parsing/parsing.c parsing/split.c parsing/keymanip.c\
			parsing/termcap.c \
			\
			execution/execution.c execution/dup_fork_wait_execute.c
OBJ 	=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
CFLAGS	=	-Wall -Wextra -Werror -g #-fsanitize=address

all: $(NAME)

bonus: all

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -lncurses -ltermcap $(OBJ) -o $(NAME)
	@echo 'Compilation Done'

$(OBJDIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
#	@echo 'Cleaning OK'

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re bonus
