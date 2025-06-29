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

static void	process_output_redirection(t_token **token_tmp, \
										t_token_exc *command)
{
	t_token	*redir_token;
	int		fd;

	redir_token = *token_tmp;
	*token_tmp = (*token_tmp)->next;
	if (*token_tmp && ft_strncmp((*token_tmp)->value, "/dev/stdout", 12) != 0)
	{
		if (redir_token->type == REDIR_OUT)
			fd = open((*token_tmp)->value, O_CREAT | O_WRONLY | \
				O_TRUNC, 0640);
		else
			fd = open((*token_tmp)->value, O_CREAT | O_WRONLY | \
				O_APPEND, 0640);
		command->fd_out = fd;
	}
}

static void	process_input_redirection(t_token **token_tmp, t_token_exc *command)
{
	int	fd;

	*token_tmp = (*token_tmp)->next;
	if (*token_tmp)
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

void	apply_redirections_to_command(t_token *cmd_tokens, t_token_exc *command)
{
	t_token	*token_tmp;

	if (!cmd_tokens || !command)
		return ;
	token_tmp = cmd_tokens;
	while (token_tmp)
	{
		if (token_tmp->type == REDIR_OUT || token_tmp->type == APPEND)
		{
			process_output_redirection(&token_tmp, command);
		}
		else if (token_tmp->type == REDIR_IN)
		{
			process_input_redirection(&token_tmp, command);
		}
		token_tmp = token_tmp->next;
	}
}
