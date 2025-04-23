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

static void	redir_out_count(t_token **token, t_echo	*echo_struct)
{
	t_token	*token_tmp;
	char	**msg_tmp;
	int		i;
	
	if (!token)
		return ;
	token_tmp = (*token);
	i = 0;
	msg_tmp = echo_struct->msg;
	while (token_tmp)
	{
		if (token_tmp->type == REDIR_OUT)
		{
			token_tmp = token_tmp->next;
			echo_struct->fd = open(token_tmp->value, O_RDWR);
		}
		else if ((token_tmp->type == WORD))
		{
			msg_tmp[i] = token_tmp->value;
			i++;
		}
		token_tmp = token_tmp->next;
	}
	echo_struct->msg = msg_tmp;
}

static void	ft_echo_helper(t_token **token, t_echo *echo_struct)
{
	char	*s;
	t_token	*token_tmp;
	t_echo	*echo_struct_tmp;

	token_tmp = *token;
	echo_struct_tmp = echo_struct;
	token_tmp = (token_tmp)->next;
	while (token_tmp != NULL)
	{
		if ((token_tmp->type == WORD) || (token_tmp->type == REDIR_OUT))
		{
			if (token_tmp->type == REDIR_OUT)
				token_tmp = token_tmp->next->next;
			else if ((ft_strncmp(token_tmp->value, "echo", 4) == 0)
				|| (ft_strncmp(token_tmp->value, "-n", 2) == 0))
				token_tmp = token_tmp->next;
			else
			{
				s = token_tmp->value;
				while (*s)
				{
					write(echo_struct_tmp->fd, s, 1);
					s++;
				}
			}
		}
		else
			print_error_command(token);
		token_tmp = token_tmp->next;
	}
}

void	ft_echo(t_token **token, t_echo *echo_struct)
{
	t_echo	*echo_struct_tmp;
	t_token	*token_tmp;
	char	*s;

	if ((!token) || (ft_strncmp((*token)->value, "echo", 4) != 0))
		return ;
	token_tmp = (*token);
	echo_struct_tmp = echo_struct;
	redir_out_count(token, echo_struct);
	if (token_tmp->type == WORD)
	{
		if (ft_strncmp(token_tmp->value, "echo", 4) == 0)
		{
			*token = token_tmp->next;
			if (token_tmp->type != WORD)
				print_echo_error();
			if (ft_strncmp(token_tmp->value, "-n", 2) == 0)
				ft_echo_helper(token, &echo_struct);
			else if ((token_tmp->type == WORD) || (token_tmp->type == REDIR_OUT))
			{
				if (token_tmp->type == REDIR_OUT)
					token_tmp = token_tmp->next->next;
				else
				{
					s = token_tmp->value;
					while (*s)
					{
						write(echo_struct_tmp->fd, s, 1);
						s++;
					}
					write(echo_struct_tmp->fd, "\n", 1);
					*token = token_tmp->next;
				}
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
	ft_echo(token, &echo_struct);
	ft_cd(token);
}
