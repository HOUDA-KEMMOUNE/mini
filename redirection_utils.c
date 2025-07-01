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

static int	handle_output_redir_range(t_token **token_tmp, t_token *end,
			t_token_exc *command)
{
	t_token	*redir_token;
	int		fd;

	redir_token = *token_tmp;
	*token_tmp = (*token_tmp)->next;
	if (*token_tmp && *token_tmp != end
		&& ft_strncmp((*token_tmp)->value, "/dev/stdout", 12) != 0)
	{
		if (redir_token->type == REDIR_OUT)
			fd = open((*token_tmp)->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		else
			fd = open((*token_tmp)->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd((*token_tmp)->value, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			*exit_status_func() = 1;
			return (-1);
		}
		if (command->fd_out != STDOUT_FILENO)
			close(command->fd_out);
		command->fd_out = fd;
	}
	return (0);
}

static int	handle_input_redir_range(t_token **token_tmp, t_token *end,
			t_token_exc *command)
{
	int	fd;

	*token_tmp = (*token_tmp)->next;
	if (*token_tmp && *token_tmp != end)
	{
		fd = open((*token_tmp)->value, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd((*token_tmp)->value, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			*exit_status_func() = 1;
			return (-1);
		}
		if (command->fd_in != STDIN_FILENO)
			close(command->fd_in);
		command->fd_in = fd;
	}
	return (0);
}

int	apply_redirections_for_command_range(t_token *start,
			t_token *end, t_token_exc *command)
{
	t_token	*token_tmp;

	if (!start || !command)
		return (0);
	token_tmp = start;
	while (token_tmp && token_tmp != end)
	{
		if (token_tmp->type == REDIR_OUT || token_tmp->type == APPEND)
		{
			if (handle_output_redir_range(&token_tmp, end, command) == -1)
				return (-1);
		}
		else if (token_tmp->type == REDIR_IN)
		{
			if (handle_input_redir_range(&token_tmp, end, command) == -1)
				return (-1);
		}
		if (token_tmp)
			token_tmp = token_tmp->next;
	}
	return (0);
}
