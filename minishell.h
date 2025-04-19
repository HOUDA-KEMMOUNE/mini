/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:32:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/04/13 17:17:43 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include "libft.h"
// #include <readline/history.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
}	t_token_type;

typedef struct s_token
{
	char *value;
	t_token_type type;
	struct s_token *next;
}	t_token;


/*-------------------errors-------------------*/
int		is_quote_closed(char *input, char quote, int start);
void	print_error(char *msg);
void	print_error_command(void);
void	print_echo_error(void);

/*-------------------Lexer-------------------*/
t_token	*lexer(char *input);
void	word_case(char *input, int *i, t_token **token_list);
void	add_token(t_token **head, char *value, t_token_type type);

/*-------------------Parsing-------------------*/
void    parsing(char *input, t_token **token);
void	ft_echo(t_token **token);

# endif
