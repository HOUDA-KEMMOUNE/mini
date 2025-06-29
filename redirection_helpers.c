/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:00:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/29 10:00:00 by akemmoun         ###   ########.fr       */
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

static void	handle_output_redirection(t_token **token_tmp, t_token *end, \
										t_token_exc *command)
{
	t_token	*redir_token;
	int		fd;

	redir_token = *token_tmp;
	*token_tmp = (*token_tmp)->next;
	if (*token_tmp && *token_tmp != end && \
		ft_strncmp((*token_tmp)->value, "/dev/stdout", 12) != 0)
	{
		open_file(&fd, &redir_token, token_tmp);
		command->fd_out = fd;
	}
}

static void	handle_input_redirection(t_token **token_tmp, t_token *end, \
									t_token_exc *command)
{
	int	fd;

	*token_tmp = (*token_tmp)->next;
	if (*token_tmp && *token_tmp != end)
	{
		fd = open((*token_tmp)->value, O_RDONLY);
		if (fd >= 0)
			command->fd_in = fd;
		else
		{
			ft_putstr_fd("minishell: ", 1);
			perror((*token_tmp)->value);
		}
	}
}

void	apply_redirections_for_command_range(t_token *start, t_token *end, \
											t_token_exc *command)
{
	t_token	*token_tmp;

	if (!start || !command)
		return ;
	token_tmp = start;
	while (token_tmp && token_tmp != end)
	{
		if (token_tmp->type == REDIR_OUT || token_tmp->type == APPEND)
		{
			handle_output_redirection(&token_tmp, end, command);
		}
		else if (token_tmp->type == REDIR_IN)
		{
			handle_input_redirection(&token_tmp, end, command);
		}
		if (token_tmp)
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
	while (current_cmd && current_token)
	{
		cmd_end = current_token;
		while (cmd_end && ft_strncmp(cmd_end->value, "|", 1) != 0)
			cmd_end = cmd_end->next;
		apply_redirections_for_command_range(cmd_start, cmd_end, current_cmd);
		if (cmd_end && ft_strncmp(cmd_end->value, "|", 1) == 0)
		{
			current_token = cmd_end->next;
			cmd_start = current_token;
			current_cmd = current_cmd->next;
		}
		else
			break ;
	}
}
