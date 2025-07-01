/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:32:30 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/29 22:34:12 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_output_file(t_token *redir_token, char *filename)
{
	int	fd;

	if (redir_token->type == REDIR_OUT)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

int	process_output_redirection(t_token **token_tmp,
		t_token_exc *command)
{
	t_token	*redir_token;
	int		fd;

	redir_token = *token_tmp;
	*token_tmp = (*token_tmp)->next;
	if (*token_tmp && ft_strncmp((*token_tmp)->value, "/dev/stdout", 12) != 0)
	{
		fd = open_output_file(redir_token, (*token_tmp)->value);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror((*token_tmp)->value);
			*exit_status_func() = 1;
			return (-1);
		}
		if (command->fd_out != STDOUT_FILENO)
			close(command->fd_out);
		command->fd_out = fd;
	}
	return (0);
}

int	process_input_redirection(t_token **token_tmp, t_token_exc *command)
{
	int	fd;

	*token_tmp = (*token_tmp)->next;
	if (*token_tmp)
	{
		fd = open((*token_tmp)->value, O_RDONLY);
		if (fd == -1)
			return (-1);
		if (command->fd_in != STDIN_FILENO)
			close(command->fd_in);
		command->fd_in = fd;
	}
	return (0);
}

int	process_redirection_token(t_token **token_tmp,
		t_token_exc **command)
{
	t_token	*redir_token;
	int		fd;

	redir_token = *token_tmp;
	*token_tmp = (*token_tmp)->next;
	if (*token_tmp && ft_strncmp((*token_tmp)->value, "/dev/stdout", 12) != 0)
	{
		fd = open_file_with_error_check(&redir_token, token_tmp);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror((*token_tmp)->value);
			*exit_status_func() = 1;
			return (-1);
		}
		if ((*command)->fd_out != STDOUT_FILENO)
			close((*command)->fd_out);
		(*command)->fd_out = fd;
	}
	return (0);
}

int	process_single_command_redirections(t_token **current_token,
		t_token_exc **current_cmd)
{
	t_token	*cmd_start;
	t_token	*cmd_end;

	cmd_start = *current_token;
	cmd_end = *current_token;
	while (cmd_end && cmd_end->type != PIPE)
		cmd_end = cmd_end->next;
	if (apply_redirections_for_command_range(cmd_start,
			cmd_end, *current_cmd) == -1)
		return (-1);
	if (cmd_end && cmd_end->type == PIPE)
	{
		*current_token = cmd_end->next;
		*current_cmd = (*current_cmd)->next;
		return (1);
	}
	return (0);
}
