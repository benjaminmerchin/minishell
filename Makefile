NAME	=	minishell
CC		=	clang
HEADER	=	includes/minishell.h
OBJDIR	=	object
SRC		=	minishell.c utils/utils.c parsing/parsing.c utils/gnl.c\
			utils/gnl_utils.c
OBJ 	=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
CFLAGS	=	-Wall -Wextra -Werror -g#-fsanitize=address

all: $(NAME)

bonus: all

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
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