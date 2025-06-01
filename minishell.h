/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:59:11 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/01 13:56:17 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
// #include <limits.h>
#include <linux/limits.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "./libft/libft.h"
// #include "./get_next_line/get_next_line.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
// #include <readline/history.h>

typedef enum	e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
}				t_token_type;

typedef struct	s_token
{
	char			*value;
	t_token_type	type;
	char			quote;
	struct s_token	*next;
}				t_token;

// 3la 9bal redirections o dak tkharbi9
typedef struct	s_token_exc
{
	char			*value;
	char			*cmd;
	char			**args;
	char			*file;
	int				fd_in;
	int				fd_out;
	t_token_type	type;
	struct s_token_exc	*next;
}				t_token_exc;

typedef struct	s_echo
{
	int		fd;
	char	*file;
	char	*input;
	char	**msg;
}				t_echo;

typedef struct	s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

// to call builtins
typedef struct s_built
{
    char *cmd;
    int (*ptr)(t_token *tokens, t_env *env);
} t_built;


/*-------------------errors-------------------*/
int		is_quote_closed(char *input, char quote, int start);
void	print_error(char *msg);
void	print_error_command(t_token **token);
void	print_echo_error(void);

/*-------------------Lexer-------------------*/
t_token	*lexer(char *input);
void	word_case(char *input, int *i, t_token **token_list);
void	add_token(t_token **head, char *value, t_token_type type, char quote);

/*-------------------Parsing-------------------*/
void    parsing(char *input, t_token **token, t_echo **echo_struct, t_env *env_list);
void	ft_data_init(t_echo	**echo_struct);
void	ft_echo(t_token **token, t_echo **echo_struct);
void	ft_cd(t_token **token, t_env *env_list);
void	ft_ls(t_token **token, t_env *env_list);
void	ft_export(t_token **token);
void	ft_unset(t_token **token);
int		is_notForbidden_char(char c);
int		check_commande(char *input);
void	ft_count(char *s, int *count);
void	ft_count_dotes(t_token **token);
void	ft_env(t_token **token, t_env *env_list);
void	ft_exit(t_token **token);

/*-------------------expander-------------------*/
t_token *expander(t_token *token_list, t_env *env_list);
char	*expand_variable(char *value, t_env *env_list);

/*-------------------execution-------------------*/
t_env		*create_env_list(char **envp);
char		*get_env_value(t_env *env, char *key);
void		get_env(t_env *env_list);
void		ft_pwd(t_token **token);
t_token_exc	*tokens_exc_handler(t_token *token);

/*-------------------helpers-------------------*/
int		ft_strcmp(const char *s1, const char *s2);
void	ft_envadd_back(t_env **lst, t_env *new);
void	ft_append(t_token **token);

/*-------------------signals-------------------*/
void	handler_sigint(int sig_num);
void	disable_sig(void);

/*----------------get_next_line-----------------*/
char	*get_next_line(int fd);
char	*rest_char(char *line);
char	*get_line(char *buffer, char *rest, int fd);
// int		ft_signals(void);

/*----------------builtins-----------------*/
int run_builtin(char *cmd, t_token *tokens, t_env *env);

/*----------------cd-----------------*/
char **token_to_args(t_token *tokens);
int cd(t_token *tokens, t_env *env);
int ft_cd_exec(t_token **tokens, t_env *env_list);
// void    pwd(t_token **token);
int pwd(t_token *tokens, t_env *env);

/*------------tokens_exec_helper1---------------*/
void	tokens_exc_helper1(t_token_exc **new, t_token **token);
void	tokens_exc_helper2(t_token_exc **new, t_token_exc **token_list);
int	ft_count_args(t_token *token);

# endif