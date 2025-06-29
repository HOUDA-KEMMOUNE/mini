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

static int	skip_redirection_tokens(t_token **current)
{
	if (!current || !(*current))
		return (0);
	if ((*current)->type == REDIR_OUT || (*current)->type == REDIR_IN
		|| (*current)->type == APPEND || (*current)->type == HEREDOC)
	{
		*current = (*current)->next;
		if (*current && ((*current)->type == WORD
				|| (*current)->type == FILE_NAME))
			*current = (*current)->next;
		return (1);
	}
	return (0);
}

static int	find_command_in_tokens(t_token *current, t_token_exc *new)
{
	while (current && current->type != PIPE)
	{
		if (skip_redirection_tokens(&current))
			continue ;
		else if (current->type == WORD)
		{
			new->cmd = current->value;
			return (1);
		}
		else if (current)
			current = current->next;
	}
	return (0);
}

static void	set_command_value(t_token **token_tmp, t_token_exc *new)
{
	t_token	*start;
	t_token	*current;

	if (!token_tmp || !(*token_tmp) || !new)
	{
		if (new)
			new->cmd = NULL;
		return ;
	}
	if ((*token_tmp)->type == HEREDOC)
	{
		new->cmd = NULL;
		return ;
	}
	start = *token_tmp;
	current = start;
	if (!find_command_in_tokens(current, new))
		new->cmd = NULL;
	*token_tmp = start;
}

void	process_command_token(t_token **token_tmp, t_token_exc **token_list)
{
	t_token		*head;
	t_token_exc	*new;

	if (!token_tmp || !(*token_tmp) || !token_list)
		return ;
	head = *token_tmp;
	new = malloc(sizeof(t_token_exc));
	if (!new)
		return ;
	ft_memset(new, 0, sizeof(t_token_exc));
	set_command_value(token_tmp, new);
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->next = NULL;
	command_node(&head, &new);
	add_token_exc_to_list(token_list, new);
	while (*token_tmp && (*token_tmp)->type != PIPE)
		*token_tmp = (*token_tmp)->next;
	if (*token_tmp && (*token_tmp)->type == PIPE)
		*token_tmp = (*token_tmp)->next;
}
