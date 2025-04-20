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
	echo_struct->msg = NULL;
}

static void	ft_echo_helper(t_token **token, t_echo	*echo_struct)
{
	char	*s;
	t_token	*token_tmp;

	token_tmp = *token;
	token_tmp = (token_tmp)->next;
	if (((token_tmp)->next->type == REDIR_OUT) && ((token_tmp)->next->type == WORD))
	{
		echo_struct->file = (token_tmp)->next->value;
		echo_struct->fd = open(echo_struct->file, O_RDWR);
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
		else
			print_error_command(token);
		while ((token_tmp) && (token_tmp->type == WORD))
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
	// token_tmp = token_tmp;
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
	else
		print_error_command(token);
}
static int	redir_out_count(t_token **token, t_echo	*echo_struct)
{
	t_token	*token_tmp;
	t_echo	*echo_struct_tmp;
	char	**msg_tmp;
	int		count_redir_out;
	int		i;
	
	if (!token)
		return ;
	token_tmp = (*token);
	echo_struct_tmp = echo_struct;
	count_redir_out = 0;
	i = 0;
	msg_tmp = echo_struct_tmp->msg;
	while (token_tmp)
	{
		if (token_tmp->type == REDIR_OUT)
			count_redir_out++;
		else if ((token_tmp->type == WORD))
		{
			msg_tmp[i] = token_tmp->value;
			i++;
		}
		// if (count_redir_out == 2)
		// 	return (count_redir_out);
		token_tmp = token_tmp->next;
	}
	echo_struct_tmp->msg = msg_tmp;
	return (count_redir_out);
}

void	ft_echo(t_token **token)
{
	t_echo	echo_struct;
	t_token	*token_tmp;
	char	*s;

	if (!token)
		return ;
	token_tmp = (*token);
	if (token_tmp->type == WORD)
	{
		if (ft_strncmp(token_tmp->value, "echo", 4) == 0)
		{
			*token = token_tmp->next;
			if (token_tmp->type != WORD)
				print_echo_error();
			if (ft_strncmp(token_tmp->value, "-n", 2) == 0)
				ft_echo_helper(token, &echo_struct);
			else if (token_tmp->type == WORD)
			{
				s = token_tmp->value;
				while (*s)
				{
					write(1, s, 1);
					s++;
				}
				write(1, "\n", 1);
				*token = token_tmp->next;
				// if ()
			}
			else
				print_error_command(token);
		}
	}
}

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
}
