/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 23:07:31 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/29 23:08:38 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file_with_error_check(t_token **redir_token, t_token **token_tmp)
{
	int	fd;

	if (!redir_token || !(*redir_token) || !token_tmp || !(*token_tmp))
		return (-1);
	if ((*redir_token)->type == REDIR_OUT)
		fd = open((*token_tmp)->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if ((*redir_token)->type == APPEND)
		fd = open((*token_tmp)->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		return (-1);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror((*token_tmp)->value);
		return (-1);
	}
	return (fd);
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

int	apply_redirections_to_command(t_token *cmd_tokens, t_token_exc *command)
{
	t_token	*token_tmp;

	if (!cmd_tokens || !command)
		return (0);
	token_tmp = cmd_tokens;
	while (token_tmp)
	{
		if (token_tmp->type == REDIR_OUT || token_tmp->type == APPEND)
		{
			if (process_output_redirection(&token_tmp, command) == -1)
				return (-1);
		}
		else if (token_tmp->type == REDIR_IN)
		{
			if (process_input_redirection(&token_tmp, command) == -1)
				return (-1);
		}
		if (token_tmp)
			token_tmp = token_tmp->next;
	}
	return (0);
}

int	check_pipeline_redirections(t_token **token, t_token_exc **command)
{
	t_token		*current_token;
	t_token_exc	*current_cmd;
	int			result;

	if (!token || !(*token) || !command || !(*command))
		return (0);
	current_token = *token;
	current_cmd = *command;
	while (current_cmd && current_token)
	{
		result = process_single_command_redirections(
				&current_token, &current_cmd);
		if (result == -1)
			return (-1);
		if (result == 0)
			break ;
	}
	return (0);
}

int	change_redout(t_token **token, t_token_exc **command)
{
	t_token	*token_tmp;

	if (!token || !(*token) || !command || !(*command))
		return (0);
	token_tmp = (*token);
	while (token_tmp)
	{
		if (token_tmp->type == REDIR_OUT || token_tmp->type == APPEND)
		{
			if (process_redirection_token(&token_tmp, command) == -1)
				return (-1);
		}
		else
			token_tmp = token_tmp->next;
	}
	return (0);
}
