/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_exec_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 13:33:32 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/25 13:53:51 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token_exc_to_list(t_token_exc **token_list, t_token_exc *new)
{
	t_token_exc	*temp;

	if ((*token_list) == NULL)
	{
		(*token_list) = new;
		return ;
	}
	temp = (*token_list);
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

static void	set_command_value(t_token **token_tmp, t_token_exc *new)
{
	if (*token_tmp && (*token_tmp)->type == HEREDOC)
	{
		new->cmd = NULL;
	}
	else
	{
		while (*token_tmp && (*token_tmp)->type != WORD
			&& (*token_tmp)->type != PIPE)
			*token_tmp = (*token_tmp)->next;
		if (*token_tmp && (*token_tmp)->type == WORD)
			new->cmd = (*token_tmp)->value;
		else
			new->cmd = NULL;
	}
}

void	process_command_token(t_token **token_tmp, t_token_exc **token_list)
{
	t_token		*head;
	t_token_exc	*new;

	head = *token_tmp;
	new = malloc(sizeof(t_token_exc));
	if (!new)
		return ;
	ft_memset(new, 0, sizeof(t_token_exc));
	set_command_value(token_tmp, new);
	new->fd_in = 0;
	new->fd_out = 1;
	new->next = NULL;
	command_node(&head, &new);
	add_token_exc_to_list(token_list, new);
	while (*token_tmp && (*token_tmp)->type != PIPE)
		*token_tmp = (*token_tmp)->next;
	if (*token_tmp && (*token_tmp)->type == PIPE)
		*token_tmp = (*token_tmp)->next;
}

void	tokens_exc_helper(t_token **token, t_token_exc **token_list)
{
	t_token	*token_tmp;

	if (!token || !(*token))
		return ;
	token_tmp = (*token);
	while (token_tmp)
	{
		process_command_token(&token_tmp, token_list);
	}
	filename_node(token);
}

void	fill_args(t_token **token, char **args_tmp, int count_args)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while ((*token) && ft_strncmp((*token)->value, "|", 1) != 0)
	{
		if ((*token)->type == WORD)
		{
			if (i < count_args)
				handle_word_token(token, args_tmp, &i, &flag);
		}
		else if ((*token)->type == HEREDOC)
		{
			handle_heredoc_token(token);
			continue ;
		}
		else if ((*token)->type == REDIR_IN || (*token)->type == REDIR_OUT || 
				(*token)->type == APPEND)
		{
			(*token) = (*token)->next; // Skip redirection operator
			if ((*token))
				(*token) = (*token)->next; // Skip filename
			continue ;
		}
		(*token) = (*token)->next;
	}
	args_tmp[i] = NULL;
}
