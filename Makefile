NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = error_msg.c lexer.c lexer_errors.c minishell.c minishell.h parsing.c\
	./libft/ft_strdup ./libft/ft_substr ./libft/ft_putstr_fd ./libft/ft_putchar_fd
	./libft/ft_strncmp 