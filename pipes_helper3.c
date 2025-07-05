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

int	check_pipe(t_token **token)
{
	t_token	*token_tmp;

	if (!token || !(*token))
		return (0);
	if (se_redirections_pipe(token) == -1)
		return (-1);
	token_tmp = (*token);
	while (token_tmp)
	{
		if (ft_strncmp(token_tmp->value, "|", 1) == 0)
		{
			token_tmp = token_tmp->next;
			if (ft_strncmp(token_tmp->value, "|", 1) == 0)
			{
				ft_putstr_fd("minishell: syntax error \
near unexpected token `|'\n", 1);
				return (-1);
			}
		}
		else if (ft_strncmp(token_tmp->value, "||", 2) == 0)
			return (-1);
		token_tmp = token_tmp->next;
	}
	return (1);
}

int	handle_fork_error(int pipe_fds[][2], int count, pid_t pids[], int i)
{
	int	j;

	perror("fork");
	close_all_pipes(pipe_fds, count - 1);
	j = 0;
	while (j < i)
	{
		kill(pids[j], SIGTERM);
		j++;
	}
	j = 0;
	while (j < i)
	{
		waitpid(pids[j], NULL, 0);
		j++;
	}
	return (0);
}
