/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:24:35 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/29 22:25:00 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_input_line(char *line, t_shell_data *data)
{
	data->tokens = lexer(line);
	if (data->tokens == NULL)
		return ;
	if (check_pipe(&data->tokens) < 0)
		return ;
	add_type(&data->tokens);
	data->tokens = expander(data->tokens, data->env_list);
	data->tokens = process_quotes(data->tokens);
	data->tokens_exec = tokens_exc_handler(data->tokens);
}

int	execute_builtin_with_redirection(t_shell_data *data)
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
	result = run_builtin(data->tokens_exec->cmd, data->tokens, &data->env_list);
	if (original_stdout != -1)
	{
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdout);
	}
	if (result)
		return (0);
	return (1);
}
