/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:00:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/28 10:00:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_file(int *fd, t_token **redir_token, t_token **token_tmp)
{
	if ((*redir_token)->type == REDIR_OUT)
		*fd = open((*token_tmp)->value, O_CREAT | O_WRONLY | O_TRUNC, 0640);
	else
		*fd = open((*token_tmp)->value, O_CREAT | O_WRONLY | O_APPEND, 0640);
}

void	change_redout(t_token **token, t_token_exc **command)
{
	t_token	*token_tmp;
	t_token	*redir_token;
	int		fd;

	if (!token || !(*token) || !command || !(*command))
		return ;
	token_tmp = (*token);
	fd = -1;
	while (token_tmp)
	{
		if (token_tmp->type == REDIR_OUT || token_tmp->type == APPEND)
		{
			redir_token = token_tmp;
			token_tmp = token_tmp->next;
			if (token_tmp && ft_strncmp(token_tmp->value,
					"/dev/stdout", 12) != 0)
			{
				open_file(&fd, &redir_token, &token_tmp);
				(*command)->fd_out = fd;
			}
		}
		else
			token_tmp = token_tmp->next;
	}
}

void	check_redirections(t_token **token, t_token_exc **command)
{
	t_token	*token_tmp;
	int		redir;

	if (!token || !(*token) || !command || !(*command))
		return ;
	token_tmp = (*token);
	redir = 0;
	while (token_tmp->next != NULL)
	{
		if (token_tmp->type == REDIR_OUT)
			redir++;
		token_tmp = token_tmp->next;
	}
	if (redir == 0 && ft_strncmp(token_tmp->value,
			"/dev/stdout", ft_strlen("/dev/stdout")) != 0)
		return ;
	else
		change_redout(token, command);
}

void	apply_redirections_to_command(t_token *cmd_tokens, t_token_exc *command)
{
	t_token	*token_tmp;
	int		fd;

	if (!cmd_tokens || !command)
		return ;
	
	token_tmp = cmd_tokens;
	while (token_tmp)
	{
		if (token_tmp->type == REDIR_OUT || token_tmp->type == APPEND)
		{
			t_token *redir_token = token_tmp;
			token_tmp = token_tmp->next;
			if (token_tmp && ft_strncmp(token_tmp->value,
					"/dev/stdout", 12) != 0)
			{
				if (redir_token->type == REDIR_OUT)
					fd = open(token_tmp->value, O_CREAT | O_WRONLY | O_TRUNC, 0640);
				else
					fd = open(token_tmp->value, O_CREAT | O_WRONLY | O_APPEND, 0640);
				command->fd_out = fd;
			}
		}
		else if (token_tmp->type == REDIR_IN)
		{
			token_tmp = token_tmp->next;
			if (token_tmp)
			{
				fd = open(token_tmp->value, O_RDONLY);
				if (fd >= 0)
					command->fd_in = fd;
				else
				{
					ft_putstr_fd("minishell: ", 1);
					perror(token_tmp->value);
				}
			}
		}
		token_tmp = token_tmp->next;
	}
}

void	check_pipeline_redirections(t_token **token, t_token_exc **command)
{
	t_token		*current_token;
	t_token_exc	*current_cmd;
	t_token		*cmd_start;
	t_token		*cmd_end;
	
	if (!token || !(*token) || !command || !(*command))
		return ;
	
	current_token = *token;
	current_cmd = *command;
	cmd_start = current_token;
	
	// Process each command in the pipeline
	while (current_cmd && current_token)
	{
		// Find the end of current command (pipe or end of tokens)
		cmd_end = current_token;
		while (cmd_end && ft_strncmp(cmd_end->value, "|", 1) != 0)
			cmd_end = cmd_end->next;
		
		// Apply redirections only for tokens belonging to this command
		apply_redirections_for_command_range(cmd_start, cmd_end, current_cmd);
		
		// Move to next command
		if (cmd_end && ft_strncmp(cmd_end->value, "|", 1) == 0)
		{
			current_token = cmd_end->next; // Skip pipe
			cmd_start = current_token; // Start of next command
			current_cmd = current_cmd->next;
		}
		else
			break;
	}
}

void	apply_redirections_for_command_range(t_token *start, t_token *end, t_token_exc *command)
{
	t_token	*token_tmp;
	int		fd;

	if (!start || !command)
		return ;
	
	token_tmp = start;
	while (token_tmp && token_tmp != end)
	{
		if (token_tmp->type == REDIR_OUT || token_tmp->type == APPEND)
		{
			t_token *redir_token = token_tmp;
			token_tmp = token_tmp->next;
			if (token_tmp && token_tmp != end && ft_strncmp(token_tmp->value, "/dev/stdout", 12) != 0)
			{
				if (redir_token->type == REDIR_OUT)
					fd = open(token_tmp->value, O_CREAT | O_WRONLY | O_TRUNC, 0640);
				else
					fd = open(token_tmp->value, O_CREAT | O_WRONLY | O_APPEND, 0640);
				command->fd_out = fd;
			}
		}
		else if (token_tmp->type == REDIR_IN)
		{
			token_tmp = token_tmp->next;
			if (token_tmp && token_tmp != end)
			{
				fd = open(token_tmp->value, O_RDONLY);
				if (fd >= 0)
					command->fd_in = fd;
				else
				{
					ft_putstr_fd("minishell: ", 1);
					perror(token_tmp->value);
				}
			}
		}
		if (token_tmp)
			token_tmp = token_tmp->next;
	}
}
