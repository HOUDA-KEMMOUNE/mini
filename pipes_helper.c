/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:02:50 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/29 15:02:52 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmd(t_token_exc **command)
{
	t_token_exc	*command_tmp;
	int			count;

	if (!command || !(*command))
		return (-1);
	command_tmp = (*command);
	count = 0;
	while (command_tmp)
	{
		count++;
		command_tmp = command_tmp->next;
	}
	return (count);
}

void	setup_file_descriptors(t_token_exc *cmd)
{
	if (cmd->fd_in != 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != 1)
	{
		dup2(cmd->fd_out, STDOUT_FILENO);
		close(cmd->fd_out);
	}
}

void	create_builtin_args(t_token *builtin_token, t_token_exc *cmd)
{
	t_token	*current;
	t_token	*arg_token;
	int		i;

	if (cmd->args && cmd->args[1])
	{
		current = builtin_token;
		i = 1;
		while (cmd->args[i])
		{
			arg_token = malloc(sizeof(t_token));
			if (!arg_token)
				exit(1);
			arg_token->value = cmd->args[i];
			arg_token->type = ARG;
			arg_token->quote = 0;
			arg_token->next = NULL;
			current->next = arg_token;
			current = arg_token;
			i++;
		}
	}
}

void	execute_builtin(t_token_exc *cmd, t_env **env_list)
{
	t_token	*builtin_token;
	t_token	*current;
	t_token	*next;
	int		ret;

	builtin_token = malloc(sizeof(t_token));
	if (!builtin_token)
		exit(1);
	builtin_token->value = cmd->cmd;
	builtin_token->type = CMD;
	builtin_token->quote = 0;
	builtin_token->next = NULL;
	create_builtin_args(builtin_token, cmd);
	ret = run_builtin(cmd->cmd, builtin_token, env_list);
	current = builtin_token;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	exit(ret);
}

void	execute_external(t_token_exc *cmd, char **envp)
{
	if (cmd->cmd_path)
		execve(cmd->cmd_path, cmd->args, envp);
	else if (cmd->cmd)
		execve(cmd->cmd, cmd->args, envp);
	perror("execve failed");
	exit(127);
}
