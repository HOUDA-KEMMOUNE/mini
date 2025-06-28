/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 01:55:44 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/28 01:55:46 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_token_exc **command)
{
	t_token_exc *command_tmp;
	int         count;
	
	if (!command || !(*command))
		return (-1);
	command_tmp = (*command);
	count = 0;
	while (command_tmp)
	{
		count++;
		// printf("command->cmd === %s (count_cmd/pipes)\n", command_tmp->cmd);
		command_tmp = command_tmp->next;
	}
	// (*command)->count_cmd = count;
	return (count);
}

void	pipes(t_token **token, t_token_exc **command)
{
	// int		count;
	// int		pipes_arr[];

	if (!token || !(*token) || !command || !(*command))
		return;
	// count = count_cmd(command);
	// if ( <= 0)
	// 	return ;
	// printf("count === %d (pipes)\n", count);
}
