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

int	handle_command_execution(t_shell_data *data, char *line)
{
	if (se_redirections(&data->tokens) <= 0)
		return (0);
	parsing(line, &data->tokens, data->env_list);
	if (count_cmd(&data->tokens_exec) <= 1)
	{
		tokens_exc_redio(data->tokens, &data->tokens_exec);
		if (check_pipeline_redirections(&data->tokens, \
			&data->tokens_exec) == -1)
			return (0);
	}
	if (!check_empty_commands(data))
		return (0);
	return (execute_commands(data));
}

static int	handle_null_cmd_with_tokens(t_shell_data *data, char **line)
{
	if (data->tokens->type == HEREDOC)
	{
		if (!handle_heredoc_tokens(data))
			return (0);
	}
	else
	{
		if (!process_redirection_tokens(data))
		{
			cleanup_resources(line, &data->tokens, &data->tokens_exec);
			return (1);
		}
	}
	cleanup_resources(line, &data->tokens, &data->tokens_exec);
	return (1);
}

static int	handle_null_command(t_shell_data *data, char **line)
{
	t_token_exc	*current;

	if (data->tokens_exec && data->tokens_exec->cmd == NULL && data->tokens)
		return (handle_null_cmd_with_tokens(data, line));
	current = data->tokens_exec;
	if (check_empty_command_loop(current, line, data))
		return (1);
	if (data->tokens_exec == NULL || data->tokens_exec->cmd == NULL)
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
