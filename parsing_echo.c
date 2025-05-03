/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:03:38 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/04/24 10:03:44 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_out_count(t_token **token, t_echo	*echo_struct)
{
	t_token	*token_tmp;
	// char	**msg_tmp;
	int		i;
	
	if (!token || !(*token))
		return ;
	token_tmp = (*token);
	i = 0;
	// msg_tmp = echo_struct->msg;
	while (token_tmp)
	{
		if (token_tmp->type == REDIR_OUT)
		{
			token_tmp = token_tmp->next;
			echo_struct->fd = open(token_tmp->value, O_RDWR);
		}
		else if (token_tmp->type == WORD)
		{
			// msg_tmp[i] = token_tmp->value;
			i++;
		}
		token_tmp = token_tmp->next;
	}
	// echo_struct->msg = msg_tmp;
}

static void	ft_echo_helper(t_token **token_tmp, t_echo *echo_struct, int *i)
{
	char	*s;
	// int		i;
	t_echo	*echo_struct_tmp;

	// i = 0;
	echo_struct_tmp = echo_struct;
	(*token_tmp) = (*token_tmp)->next;
	while (*token_tmp != NULL)
	{
		if (((*token_tmp)->type == WORD) || ((*token_tmp)->type == REDIR_OUT))
		{
			if ((*token_tmp)->type == REDIR_OUT)
			{
				(*token_tmp) = (*token_tmp)->next->next;
				if ((*token_tmp) == NULL)
					return ;
			}
			else if (ft_strncmp((*token_tmp)->value, "echo", 4) == 0)
			{
				if ((ft_strncmp((*token_tmp)->next->value, "-n", 2) == 0)
				&& (*i > 0))
					write(echo_struct_tmp->fd, " echo -n ", 9);
				else
				{
					(*token_tmp) = (*token_tmp)->next;
					// write(echo_struct_tmp->fd, " ", 1);
				}
				(*i)++;
			}
			if ((*token_tmp) != NULL)
			{
				s = (*token_tmp)->value;
				while (*s)
				{
					write(echo_struct_tmp->fd, s, 1);
					s++;
				}
			}
		}
		else
			print_error_command(token_tmp);
		(*token_tmp) = (*token_tmp)->next;
	}
}

void	ft_echo(t_token **token, t_echo *echo_struct)
{
	t_echo	*echo_struct_tmp;
	t_token	*token_tmp;
	char	*s;
	int		i;

	i = 0;
	if ((!token) || (ft_strncmp((*token)->value, "echo", 4) != 0))
		return ;
	token_tmp = (*token);
	echo_struct_tmp = echo_struct;
	redir_out_count(token, echo_struct);
	if (token_tmp->type == WORD)
	{
		while (token_tmp)
		{
			if (ft_strncmp(token_tmp->value, "echo", 4) == 0)
			{
				if ((ft_strncmp(token_tmp->next->value, "-n", 2) == 0)
				&& (i > 0))
					write(echo_struct_tmp->fd, " echo -n ", ft_strlen(" echo -n "));
				else
				{
					token_tmp = token_tmp->next;
					// write(echo_struct_tmp->fd, " ", 1);
				}
				i++;
			}
			if (token_tmp->type != WORD)
				print_echo_error();
			if (ft_strncmp(token_tmp->value, "-n", 2) == 0)
				ft_echo_helper(&token_tmp, echo_struct, &i);
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
					token_tmp = token_tmp->next;
					write(echo_struct_tmp->fd, " ", 1);
				}
			}
			else
				print_error_command(token);
		}
	}
	return ;
}
