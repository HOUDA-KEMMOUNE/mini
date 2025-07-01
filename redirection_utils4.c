/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:00:00 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/07/01 00:00:00 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*find_command_tokens(t_token *tokens, int cmd_index)
{
	t_token	*current;
	int		pipe_count;

	if (!tokens)
		return (NULL);
	current = tokens;
	pipe_count = 0;
	while (current && pipe_count < cmd_index)
	{
		if (current->type == PIPE)
			pipe_count++;
		current = current->next;
	}
	return (current);
}

static t_token	*find_command_end(t_token *start)
{
	t_token	*current;

	if (!start)
		return (NULL);
	current = start;
	while (current && current->type != PIPE)
		current = current->next;
	return (current);
}

int	check_individual_command_redirections(t_token *tokens, t_token_exc *cmd,
		int cmd_index)
{
	t_token	*cmd_start;
	t_token	*cmd_end;

	if (!tokens || !cmd)
		return (0);
	cmd_start = find_command_tokens(tokens, cmd_index);
	if (!cmd_start)
		return (0);
	cmd_end = find_command_end(cmd_start);
	return (apply_redirections_for_command_range(cmd_start, cmd_end, cmd));
}

int	check_redirections(t_token **token, t_token_exc **command)
{
	t_token	*token_tmp;
	int		redir;

	if (!token || !(*token) || !command || !(*command))
		return (0);
	token_tmp = (*token);
	redir = 0;
	while (token_tmp)
	{
		if (token_tmp->type == REDIR_OUT || token_tmp->type == APPEND)
			redir++;
		token_tmp = token_tmp->next;
	}
	if (redir == 0)
		return (0);
	else
		return (change_redout(token, command));
}
