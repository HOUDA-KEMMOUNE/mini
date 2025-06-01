/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:07:23 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/01 15:07:24 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_fd(t_token_exc **token_cmd)
{
	if ((*token_cmd)->fd_in != 0)
	{
		dup2((*token_cmd)->fd_in, 0);
		close((*token_cmd)->fd_in);
	}
	if ((*token_cmd)->fd_out != 1)
	{
		dup2((*token_cmd)->fd_out, 1);
		close((*token_cmd)->fd_out);
	}
}

void	simple_cmd(t_token *token, t_token_exc **token_cmd)
{
	int	pid;

	pid = fork();
	// if (pid < 0)
	// {
	// 	perror("");
	// }
	if (pid == 0) //child
	{
		//execve(path, args, env); path = /usr/bin/cat
	}
}
