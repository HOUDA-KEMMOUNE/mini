/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:00:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/27 16:00:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_handle_empty_cmd(t_echo *echo_struct_tmp)
{
	ft_putstr_fd("\n", echo_struct_tmp->fd);
}

int	echo_handle_n_flag(t_token **token_tmp)
{
	if (ft_strncmp((*token_tmp)->value, "-n", 2) == 0)
	{
		if ((*token_tmp)->next == NULL)
			return (1);
		(*token_tmp) = (*token_tmp)->next;
		return (1);
	}
	return (0);
}

void	echo_write_char_by_char(t_token *token_tmp, t_echo *echo_struct_tmp)
{
	char	*s;

	s = token_tmp->value;
	while (*s)
	{
		if ((ft_strncmp(s, ">", 1) == 0) || (ft_strncmp(s, ">>", 2) == 0))
			break ;
		write(echo_struct_tmp->fd, s, 1);
		s++;
	}
}

static void	echo_handle_redirection_skip(t_token **token_tmp)
{
	if ((ft_strncmp((*token_tmp)->value, ">", 1) == 0)
		|| (ft_strncmp((*token_tmp)->value, ">>", 2) == 0))
		(*token_tmp) = (*token_tmp)->next->next;
	else
		(*token_tmp) = (*token_tmp)->next;
}

void	echo_process_args(t_token **token, t_token *token_tmp,
			t_echo *echo_struct_tmp, t_env *env_list)
{
	while (token_tmp)
	{
		if (token_tmp->type == PIPE)
			break ;
		if (ft_strchr(token_tmp->value, '$'))
		{
			(*token) = echo_expander(*token, env_list, echo_struct_tmp->fd);
			return ;
		}
		echo_write_char_by_char(token_tmp, echo_struct_tmp);
		if ((token_tmp->next != NULL))
			write(echo_struct_tmp->fd, " ", 1);
		echo_handle_redirection_skip(&token_tmp);
	}
}

void	echo_process_main_logic(t_token **token, t_token *head,
			t_echo *echo_struct_tmp, t_env *env_list)
{
	t_token	*token_tmp;
	int		n_flag;

	token_tmp = *token;
	if (token_tmp->next == NULL)
	{
		echo_handle_empty_cmd(echo_struct_tmp);
		return ;
	}
	token_tmp = token_tmp->next;
	n_flag = echo_handle_n_flag(&token_tmp);
	if ((token_tmp->type == ARG) || (token_tmp->type == REDIR_OUT)
		|| (token_tmp->type == APPEND))
	{
		echo_process_args(token, token_tmp, echo_struct_tmp, env_list);
		if (!n_flag || ft_strncmp(head->value, "-n", 2) != 0)
			write(echo_struct_tmp->fd, "\n", 1);
	}
}
