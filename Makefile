NAME	=	minishell
CC		=	clang
HEADER	=	includes/minishell.h
OBJDIR	=	object
SRC		=	minishell.c \
			\
			utils/utils.c utils/gnl_utils.c utils/gnl.c utils/libft_lst.c \
			utils/utils2.c utils/clean_exit.c utils/libft.c utils/libft_split.c \
			utils/libft_itoa.c \
			\
			parsing/parsing.c parsing/split.c parsing/keymanip.c \
			parsing/termcap.c parsing/manage_antislash_parsing.c \
			parsing/calcul_nbr_token.c parsing/calcul_nbr_token_2.c \
			\
			execution/execution.c execution/fork_wait_execute.c execution/expansion_dup.c \
			execution/signals.c
OBJ 	=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address

ifneq (,$(findstring xterm,${TERM}))
	GREEN := $(shell tput -Txterm setaf 2)
	RESET := $(shell tput -Txterm sgr0)
else
	GREEN := ""
	RESET := ""
endif

all: $(NAME)

bonus: all

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -lncurses -ltermcap $(OBJ) -o $(NAME)
	@echo "${GREEN}Compilation Done${RESET}"

$(OBJDIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
#	@echo 'Cleaning OK'

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re bonus
