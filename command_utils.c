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

void	process_input_line(char *line, t_shell_data *data)
{
	data->tokens = lexer(line);
	if (data->tokens == NULL)
		return ;
	add_type(&data->tokens);
	data->tokens = expander(data->tokens, data->env_list);
	data->tokens_exec = tokens_exc_handler(data->tokens);
}

int	handle_command_execution(t_shell_data *data, char *line)
{
	if (se_redirections(&data->tokens) <= 0)
		return (0);
	parsing(line, &data->tokens, data->env_list);
	pipes(&data->tokens, &data->tokens_exec);
	tokens_exc_redio(data->tokens, &data->tokens_exec);
	check_redirections(&data->tokens, &data->tokens_exec);
	echo(&data->tokens, &data->tokens_exec);
	heredoc(&data->tokens, &data->tokens_exec);
	if (is_builtin(&data->tokens_exec) == 1)
	{
		path(&data->tokens_exec);
		if (data->tokens_exec->cmd_path)
			simple_cmd(data->tokens, &data->tokens_exec);
		return (0);
	}
	if (run_builtin(data->tokens->value, data->tokens, &data->env_list))
		return (0);
	return (1);
}

int	process_command_line(char *line, t_shell_data *data)
{
	process_input_line(line, data);
	if (data->tokens == NULL)
	{
		free(line);
		return (1);
	}
	
	// Handle the case where there's a command but it's NULL (heredoc without command)
	if (data->tokens_exec && data->tokens_exec->cmd == NULL)
	{
		// Check if there are any heredocs to process
		if (data->tokens && data->tokens->type == HEREDOC)
		{
			heredoc(&data->tokens, &data->tokens_exec);
		}
		cleanup_resources(&line, &data->tokens,
			&data->tokens_exec);
		return (1);
	}
	
	if (data->tokens_exec == NULL || data->tokens_exec->cmd == NULL
		|| data->tokens_exec->cmd[0] == '\0')
	{
		cleanup_resources(&line, &data->tokens,
			&data->tokens_exec);
		return (1);
	}
	if (data->tokens)
	{
		if (!handle_command_execution(data, line))
		{
			cleanup_resources(&line, &data->tokens,
				&data->tokens_exec);
			return (1);
		}
	}
	cleanup_resources(&line, &data->tokens,
		&data->tokens_exec);
	return (0);
}
