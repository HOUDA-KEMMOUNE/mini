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

int	execute_pipeline_fork(int pipe_fds[][2], pid_t pids[],
		t_token_exc *cmd_current, int count)
{
	int	i;

	i = 0;
	while (cmd_current && i < count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (-1);
		else if (pids[i] == 0)
		{
			setup_child_pipes(cmd_current, pipe_fds, i, count - 1);
			close_unused_pipes(pipe_fds, count - 1, i);
			execute_pipeline_command(cmd_current, NULL, NULL);
		}
		cmd_current = cmd_current->next;
		i++;
	}
	return (0);
}

int	execute_pipeline(int pipe_fds[][2], pid_t pids[], t_token_exc *cmd_current,
		int count)
{
	int	status;

	if (execute_pipeline_fork(pipe_fds, pids, cmd_current, count) == -1)
		return (-1);
	close_all_pipes(pipe_fds, count - 1);
	status = wait_for_children(pids, count);
	return (status);
}

int	setup_pipeline_execution(t_token_exc **command, t_env *env_list)
{
	t_token_exc	*cmd_current;

	(void)env_list;
	cmd_current = *command;
	while (cmd_current)
	{
		path(&cmd_current);
		cmd_current = cmd_current->next;
	}
	return (0);
}

int	pipes(t_token **token, t_token_exc **command, t_env *env_list)
{
	int			count;
	int			pipe_fds[32][2];
	pid_t		pids[33];
	char		**envp;
	int			result;

	if (!token || !(*token) || !command || !(*command))
		return (0);
	count = count_cmd(command);
	if (count <= 1)
		return (0);
	setup_pipeline_execution(command, env_list);
	envp = env_to_array(env_list);
	if (!envp)
		return (0);
	if (create_pipes(pipe_fds, count) == -1)
	{
		free_args(envp);
		return (0);
	}
	result = execute_pipeline(pipe_fds, pids, *command, count);
	*exit_status_func() = result;
	free_args(envp);
	return (result);
}
