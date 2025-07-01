/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helper2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:03:53 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/29 15:03:54 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pipeline_command(t_token_exc *cmd, t_pipeline_context *ctx)
{
	if (!cmd)
		exit(1);
	if (!cmd->cmd)
	{
		setup_file_descriptors(cmd);
		exit(0);
	}
	setup_file_descriptors(cmd);
	if (is_builtin(&cmd) == 0)
		execute_builtin(cmd, ctx->env_list);
	else
		execute_external(cmd, ctx->envp);
}

void	execute_pipeline_command_with_tokens(t_token_exc *cmd,
		t_pipeline_context *ctx)
{
	if (!cmd)
		exit(1);
	if (!cmd->cmd)
	{
		setup_file_descriptors(cmd);
		exit(0);
	}
	if (check_individual_command_redirections(ctx->tokens, cmd,
			ctx->cmd_index) == -1)
		exit(1);
	setup_file_descriptors(cmd);
	if (is_builtin(&cmd) == 0)
		execute_builtin(cmd, ctx->env_list);
	else
		execute_external(cmd, ctx->envp);
}

void	close_all_pipes(int pipe_fds[][2], int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
	}
}

void	close_unused_pipes(int pipe_fds[][2], int pipe_count, int cmd_index)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (cmd_index > 0 && i == cmd_index - 1)
			close(pipe_fds[i][1]);
		else if (cmd_index < pipe_count && i == cmd_index)
			close(pipe_fds[i][0]);
		else
		{
			close(pipe_fds[i][0]);
			close(pipe_fds[i][1]);
		}
		i++;
	}
}

void	setup_child_pipes(t_token_exc *cmd, int pipe_fds[][2],
		int cmd_index, int last_cmd_index)
{
	if (cmd->fd_in == 0)
	{
		if (cmd_index == 0)
			cmd->fd_in = 0;
		else
			cmd->fd_in = pipe_fds[cmd_index - 1][0];
	}
	if (cmd->fd_out == 1)
	{
		if (cmd_index == last_cmd_index)
			cmd->fd_out = 1;
		else
			cmd->fd_out = pipe_fds[cmd_index][1];
	}
}
