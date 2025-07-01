/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:00:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/01 10:00:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty_commands(t_shell_data *data)
{
	t_token_exc	*current;

	current = data->tokens_exec;
	while (current)
	{
		if (current->cmd && current->cmd[0] == '\0')
		{
			if (count_cmd(&data->tokens_exec) <= 1
				|| current->count_heredoc == 0)
			{
				ft_putstr_fd("minishell: : command not found\n", 2);
				*exit_status_func() = 127;
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

int	execute_commands(t_shell_data *data)
{
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

int	handle_heredoc_tokens(t_shell_data *data)
{
	t_token	*tmp;

	heredoc(&data->tokens, &data->tokens_exec);
	if (data->tokens && data->tokens->next)
	{
		tmp = data->tokens;
		while (tmp)
		{
			if (tmp->type == PIPE)
				return (0);
			tmp = tmp->next;
		}
	}
	return (1);
}

int	process_redirection_tokens(t_shell_data *data)
{
	if (se_redirections(&data->tokens) > 0)
	{
		if (count_cmd(&data->tokens_exec) <= 1)
			tokens_exc_redio(data->tokens, &data->tokens_exec);
		if (check_pipeline_redirections(&data->tokens, \
			&data->tokens_exec) == -1)
			return (0);
	}
	return (1);
}

int	check_empty_command_loop(t_token_exc *current, char **line,
		t_shell_data *data)
{
	while (current)
	{
		if (current->cmd && current->cmd[0] == '\0')
		{
			ft_putstr_fd("minishell: : command not found\n", 2);
			*exit_status_func() = 127;
			cleanup_resources(line, &data->tokens, &data->tokens_exec);
			return (1);
		}
		current = current->next;
	}
	return (0);
}
