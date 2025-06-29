/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:00:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/28 10:00:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_builtin_with_redirection(t_shell_data *data)
{
	int	original_stdout;
	int	result;

	original_stdout = -1;
	if (data->tokens_exec->fd_out != 1)
	{
		original_stdout = dup(STDOUT_FILENO);
		dup2(data->tokens_exec->fd_out, STDOUT_FILENO);
		close(data->tokens_exec->fd_out);
	}
	result = run_builtin(data->tokens->value, data->tokens, &data->env_list);
	*exit_status_func() = result;
	if (original_stdout != -1)
	{
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdout);
	}
	if (result)
		return (0);
	return (1);
}

int	handle_command_execution(t_shell_data *data, char *line)
{
	if (se_redirections(&data->tokens) <= 0)
		return (0);
	parsing(line, &data->tokens, data->env_list);
	if (count_cmd(&data->tokens_exec) <= 1)
		tokens_exc_redio(data->tokens, &data->tokens_exec);
	check_pipeline_redirections(&data->tokens, &data->tokens_exec);
	heredoc(&data->tokens, &data->tokens_exec);
	if (pipes(&data->tokens, &data->tokens_exec, data->env_list))
		return (0);
	if (is_builtin(&data->tokens_exec) == 1)
	{
		path(&data->tokens_exec);
		if (data->tokens_exec->cmd_path)
			simple_cmd(data->tokens, &data->tokens_exec);
		return (0);
	}
	return (execute_builtin_with_redirection(data));
}

static int	handle_null_command(t_shell_data *data, char **line)
{
	if (data->tokens_exec && data->tokens_exec->cmd == NULL)
	{
		if (data->tokens && data->tokens->type == HEREDOC)
		{
			heredoc(&data->tokens, &data->tokens_exec);
		}
		cleanup_resources(line, &data->tokens, &data->tokens_exec);
		return (1);
	}
	if (data->tokens_exec == NULL || data->tokens_exec->cmd == NULL
		|| data->tokens_exec->cmd[0] == '\0')
	{
		cleanup_resources(line, &data->tokens, &data->tokens_exec);
		return (1);
	}
	return (0);
}

static int	execute_and_cleanup(t_shell_data *data, char **line)
{
	if (data->tokens)
	{
		if (!handle_command_execution(data, *line))
		{
			cleanup_resources(line, &data->tokens, &data->tokens_exec);
			return (1);
		}
	}
	cleanup_resources(line, &data->tokens, &data->tokens_exec);
	return (0);
}

int	process_command_line(char *line, t_shell_data *data)
{
	process_input_line(line, data);
	if (data->tokens == NULL)
	{
		free(line);
		return (1);
	}
	if (handle_null_command(data, &line))
		return (1);
	return (execute_and_cleanup(data, &line));
}
