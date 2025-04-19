/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:23:09 by akemmoun          #+#    #+#             */
/*   Updated: 2025/04/11 13:23:10 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_data_init(t_echo	*echo_struct)
{
	t_echo	echo_struct;

	echo_struct->fd = 1;
	echo_struct->file = NULL;
	echo_struct->input = NULL;
}

static void	ft_echo_helper(t_token **token, t_echo	*echo_struct)
{
	char	*s;
	t_token	*token_tmp;

	token_tmp = *token;
	token_tmp = (token_tmp)->next;
	if (((token_tmp)->next->type == APPEND) && ((token_tmp)->next->type == WORD))
	{
		echo_struct->file = (token_tmp)->next->value;
		echo_struct->fd = open(echo_struct->file, O_RDWR);
	}
	// token_tmp = token_tmp;
	while ((token_tmp))
	{
		if ((token_tmp)->type == WORD)
		{
			echo_struct->input = (token_tmp)->value;
			s = echo_struct->input;
			while (*s)
			{
				write(echo_struct->fd, s, 1);
				s++;
			}
		}
	}
	// else
	// 	print_error_command(token);
}

void	ft_echo(t_token **token)
{
	t_echo	echo_struct;
	char	*s;
	
	if ((*token)->type == WORD)
	{
		if (ft_strncmp((*token)->value, "echo", 4) == 0)
		{
			*token = (*token)->next;
			if ((*token)->type != WORD)
				print_echo_error();
			if (ft_strncmp((*token)->value, "-n", 2) == 0)
				ft_echo_helper(token, &echo_struct);
			// hna fin wsalt hahhahahahahahahahahahahahahahahaha
			else if ((*token)->type == WORD)
			{
				s = (*token)->value;
				while (*s)
				{
					write(1, s, 1);
					s++;
				}
				write(1, "\n", 1);
				*token = (*token)->next;
				// if ()
			}
			else
				print_error_command(token);
		}
	}
}

// void	ft_cd(t_token **token)
// {
// 	char	*s;

// 	if ((*token)->type == WORD)
// 	{
// 		if (ft_strncmp((*token)->value, "cd", 2) == 0)
// 		{
// 			*token = (*token)->next;
// 			if 
			
// 		}
// 	}
// }

void    parsing(char *input, t_token **token)
{
	char	*s;
	t_echo	echo_struct;

	if (!input || !token)
		return ;
	if (*input == '|')
	{
		write(1, "minishell: parse error near `|'", ft_strlen("minishell: parse error near `|'"));
		exit (1);
	}
	else if (*input == '(')
	{
		write(1, "minishell: unclosed parenthesis `('", ft_strlen("minishell: unclosed parenthesis `('"));
		exit (1);
	}
	else if (*input == 39)
	{
		write(1, "minishell: parse error near `\''", ft_strlen("minishell: unclosed parenthesis `('"));
		exit (1);
	}
	ft_data_init(&echo_struct);
	ft_echo(token);
	// nkhadmo 3la cd ::)
	//ft_cd(token);
}
