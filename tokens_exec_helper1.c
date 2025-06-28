/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_exec_helper1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:07:55 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/25 14:04:48 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokens_exc_helper1(t_token_exc **new, t_token **token)
{
	(*new)->cmd = (*token)->value;
	(*new)->fd_in = 0;
	(*new)->fd_out = 1;
	(*new)->next = NULL;
}

void	tokens_exc_helper2(t_token_exc **new, t_token_exc **token_list)
{
	t_token_exc	*temp;

	if ((*token_list) == NULL)
		(*token_list) = (*new);
	else
	{
		temp = (*token_list);
		while (temp->next)
			temp = temp->next;
		temp->next = (*new);
	}
}

void	handle_redir(t_token *token_tmp, t_token_exc **token_list, int type)
{
	int	fd;

	token_tmp = token_tmp->next;
	(*token_list)->file = ft_strdup(token_tmp->value);
	if (type == REDIR_OUT)
		fd = open(token_tmp->value, O_CREAT | O_WRONLY | O_TRUNC, 0640);
	else if (type == APPEND)
		fd = open(token_tmp->value, O_CREAT | O_WRONLY | O_APPEND, 0640);
	else
		fd = open(token_tmp->value, O_RDONLY);
	if (type == REDIR_OUT || type == APPEND)
		(*token_list)->fd_out = fd;
	else if (type == REDIR_IN && fd < 0)
	{
		ft_putstr_fd("minishell: ", 1);
		perror((*token_list)->file);
	}
}

void	tokens_exc_redio(t_token *token, t_token_exc **token_list)
{
	t_token	*token_tmp;
	int		type;

	if (!token || !token_list || !(*token_list))
		return ;
	token_tmp = token;
	while (token_tmp)
	{
		type = token_tmp->type;
		if (type == REDIR_OUT || type == APPEND || type == REDIR_IN)
			handle_redir(token_tmp, token_list, type);
		token_tmp = token_tmp->next;
	}
}

void	handle_heredoc_token(t_token **token)
{
	(*token) = (*token)->next;
	if ((*token) && ((*token)->type == DELIMITER
			|| (*token)->type == ARG || (*token)->type == CMD))
	{
		(*token) = (*token)->next;
		return ;
	}
}
