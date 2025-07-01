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

int	execute_pipeline_fork(t_pipeline_context *ctx, int pipe_fds[][2], \
		pid_t pids[], int count)
{
	t_token_exc	*cmd_current;
	int			i;

	cmd_current = ctx->tokens_exec;
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
			ctx->cmd_index = i;
			execute_pipeline_command_with_tokens(cmd_current, ctx);
		}
		cmd_current = cmd_current->next;
		i++;
	}
	return (0);
}

int	execute_pipeline(t_pipeline_context *ctx, int pipe_fds[][2], \
		pid_t pids[], int count)
{
	if (execute_pipeline_fork(ctx, pipe_fds, pids, count) == -1)
		return (-1);
	close_all_pipes(pipe_fds, count - 1);
	*exit_status_func() = wait_for_children(pids, count);
	return (1);
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

static int	setup_pipeline_context(t_token **token, t_token_exc **command,
		t_env *env_list, t_pipeline_context *ctx)
{
	ctx->envp = env_to_array(env_list);
	if (!ctx->envp)
		return (0);
	ctx->tokens = *token;
	ctx->tokens_exec = *command;
	ctx->env_list = &env_list;
	return (1);
}

int	pipes(t_token **token, t_token_exc **command, t_env *env_list)
{
	int					count;
	int					pipe_fds[32][2];
	pid_t				pids[33];
	t_pipeline_context	ctx;
	int					result;

	if (!token || !(*token) || !command || !(*command))
		return (0);
	count = count_cmd(command);
	if (count <= 1)
		return (0);
	setup_pipeline_execution(command, env_list);
	if (!setup_pipeline_context(token, command, env_list, &ctx))
		return (0);
	if (create_pipes(pipe_fds, count) == -1)
	{
		free_args(ctx.envp);
		return (0);
	}
	result = execute_pipeline(&ctx, pipe_fds, pids, count);
	free_args(ctx.envp);
	return (result);
}
