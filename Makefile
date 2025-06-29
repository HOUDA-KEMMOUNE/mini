NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIE
LIBS = -lreadline

# Source files
SRC = minishell.c lexer.c lexer_core.c lexer_utils.c lexer_support.c lexer_helper.c lexer_errors.c error_msg.c parsing_cd.c expander.c expander2.c parsing_export.c\
	par_exec_echo.c env.c parsing_env.c parsing_unset.c parsing.c parsing_exit.c parsing_ls.c\
	helpers.c signal_hand.c get_next_line.c append.c pwd_exec.c builtins.c cd_exe.c tokens_exec.c\
	tokens_exec_helper1.c path.c simple_commands.c export_exe.c unset_exe.c free.c heredoc.c\
	export_exe_helper.c export_exe_helper2.c free2.c path_utils.c tokens_exec_utils.c simple_cmd_utils.c\
	cd_exe_helper.c pipes.c redirection_utils.c redirection_helpers.c main_helpers.c shell_loop.c command_utils.c pipes_helper.c pipes_helper2.c pipes_helper3.c\
	heredoc_helper.c

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
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LIBS) -o $(NAME)

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
