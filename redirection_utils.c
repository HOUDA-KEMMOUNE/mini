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

static int	open_redirection_file(t_token *token_tmp, int *fd)
{
	if (token_tmp->type == REDIR_OUT)
		*fd = open(token_tmp->value, O_CREAT | O_WRONLY | O_TRUNC, 0640);
	else
		*fd = open(token_tmp->value, O_CREAT | O_WRONLY | O_APPEND, 0640);
	return (*fd);
}

void	change_redout(t_token **token, t_token_exc **command)
{
	t_token	*token_tmp;
	int		fd;

	if (!token || !(*token) || !command || !(*command))
		return ;
	token_tmp = (*token);
	fd = -1;
	while (token_tmp)
	{
		if (token_tmp->type == REDIR_OUT || token_tmp->type == APPEND)
		{
			token_tmp = token_tmp->next;
			if (token_tmp && ft_strncmp(token_tmp->value,
					"/dev/stdout", 12) != 0)
			{
				open_redirection_file(token_tmp, &fd);
				(*command)->fd_out = fd;
			}
		}
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
