/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:32:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/05/17 10:48:08 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h> 
#include <sys/wait.h>
#include <termios.h>
#include <readline/readline.h>
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
t_env	*create_env_list(char **envp);
char	*get_env_value(t_env *env, char *key);

/*-------------------helpers-------------------*/
int	ft_strcmp(const char *s1, const char *s2);
void	ft_envadd_back(t_env **lst, t_env *new);

/*-------------------signals-------------------*/
void	handler_sigint(int sig_num);
void	disable_sig(void);

/*-------------------signals-------------------*/
char	*get_next_line(int fd);
char	*rest_char(char *line);
char	*get_line(char *buffer, char *rest, int fd);
// int		ft_signals(void);

# endif
