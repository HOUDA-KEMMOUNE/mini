NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRC = minishell.c lexer.c lexer_errors.c error_msg.c parsing_cd.c expander.c \
	parsing_echo.c

# Object files
OBJ = $(SRC:.c=.o)

# Libft path
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Include directory if needed
INCLUDES = -I.

all: $(NAME)

# Rule to build minishell
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

# Rule to build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
