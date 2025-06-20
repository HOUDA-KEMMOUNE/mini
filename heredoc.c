/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:05:22 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/20 16:05:23 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredoc(t_token **token, t_token_exc **command)
{
	t_token		*token_tmp;
	t_token_exc	*command_tmp;
	int			check;

	check = 0;
	token_tmp = (*token);
	command_tmp = (*command);
	while (token_tmp)
	{
		if (token_tmp->type == HEREDOC)
		{
			token_tmp = token_tmp->next;
			if (token_tmp->type == ARG)
			{
				token_tmp->type = DELIMITER;
				command_tmp->delimiter = token_tmp->value;
				check++;
			}
		}
		token_tmp = token_tmp->next;
	}
	(*command) = command_tmp;
	return (check);
}

void	heredoc(t_token **token, t_token_exc **command)
{
	t_token_exc	*command_tmp;
	t_token		*token_tmp;

	if (!token || !(*token) || !command || !(*command))
		return ;
	command_tmp = (*command);
	token_tmp = (*token);
	if (check_heredoc(token, command) == 0)
		return ;
	int i = 0;
	char **s = command_tmp->args;
	while (command_tmp)
	{
		while (s[i])
		{
			printf("command_tmp->args = %s\n", s[i]);
			i++;
		}
		printf("command_tmp->file = %s\n", command_tmp->file);
		printf("command_tmp->delimiter = %s\n", command_tmp->delimiter);
		printf("command_tmp->vakue = %s\n", command_tmp->value);
		printf("command_tmp->fd_in = %d\n", command_tmp->fd_in);
		printf("command_tmp->fd_out = %d\n", command_tmp->fd_out);
		command_tmp = command_tmp->next;
	}
}
