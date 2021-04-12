NAME	=	minishell
CC		=	clang
HEADER	=	minishell.h
OBJDIR	=	object
SRC		=	libft.c libft2.c utils.c utils2.c utils3.c ft_split.c median.c small_list.c bonus.c\
			execute_instructions_checker.c half_on_b.c execute_best_move.c find_farthest.c calculate_best_move.c \
			operation.c operation2.c operation3.c operation_write.c operation_write2.c operation_write3.c
SRC_C	=	checker.c $(SRC)
SRC_P	=	push_swap.c $(SRC)
OBJ_C 	=	$(addprefix $(OBJDIR)/, $(SRC_C:.c=.o))
OBJ_P 	=	$(addprefix $(OBJDIR)/, $(SRC_P:.c=.o))
CFLAGS	=	-Wall -Wextra -Werror -g#-fsanitize=address

all: $(NAME_C) $(NAME_P)

bonus: all

test:
	@./play.sh

$(NAME_C): $(OBJ_C)
	@$(CC) $(CFLAGS) $(OBJ_C) -o $(NAME_C)
#	@echo 'Checker Compilation OK'

$(NAME_P): $(OBJ_P)
	@$(CC) $(CFLAGS) $(OBJ_P) -o $(NAME_P)
#	@echo 'Push_swap Compilation OK'

$(OBJDIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_C) $(OBJ_P)
#	@echo 'Cleaning OK'

fclean: clean
	@rm -f $(NAME_C) $(NAME_P)

re: fclean all

.PHONY: clean fclean all re bonus