/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helper3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:27:16 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/29 15:27:18 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_for_children(pid_t pids[], int count)
{
	int	i;
	int	status;
	int	child_status;

	i = 0;
	status = 0;
	while (i < count)
	{
		waitpid(pids[i], &child_status, 0);
		if (i == count - 1 && WIFEXITED(child_status))
			status = WEXITSTATUS(child_status);
		i++;
	}
	return (status);
}

int	create_pipes(int pipe_fds[][2], int count)
{
	int	i;

	i = 0;
	while (i < count - 1)
	{
		if (pipe(pipe_fds[i]) == -1)
		{
			perror("pipe");
			close_all_pipes(pipe_fds, i);
			return (-1);
		}
		i++;
	}
	return (0);
}
