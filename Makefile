NAME	=	minishell
CC		=	clang
HEADER	=	includes/minishell.h
OBJDIR	=	object
SRC		=	minishell.c \
			utils/utils.c utils/gnl_utils.c utils/gnl.c \
			utils/utils2.c utils/clean_exit.c\
			parsing/parsing.c parsing/store_string.c parsing/split.c \
			parsing/termcap.c
OBJ 	=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address

all: $(NAME)

bonus: all

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -lncurses -ltermcap $(OBJ) -o $(NAME)
#	@echo 'Checker Compilation OK'

$(OBJDIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
#	@echo 'Cleaning OK'

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re bonus
