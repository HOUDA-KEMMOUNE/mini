/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:32:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/04/23 17:06:35 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include "./libft/libft.h"
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
	int	fd;
	char	*file;
	char	*input;
	char	**msg;
}				t_echo;

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
void    parsing(char *input, t_token **token);
void	ft_data_init(t_echo	*echo_struct);
void	ft_echo(t_token **token, t_echo *echo_struct);
void	ft_cd(t_token **token);

# endif
