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

int	count_cmd(t_token_exc **command)
{
	t_token_exc *command_tmp;
	int         count;
	
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

void	execute_pipeline_command(t_token_exc *cmd, char **envp, t_env **env_list)
{
	// Add safety checks
	if (!cmd || !cmd->cmd)
		exit(1);
		
	(void)env_list;
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
	if (is_builtin(&cmd) == 0)
	{
		t_token *builtin_token = malloc(sizeof(t_token));
		if (!builtin_token)
			exit(1);
		
		builtin_token->value = cmd->cmd;
		builtin_token->type = CMD;
		builtin_token->quote = 0;
		builtin_token->next = NULL;
		if (cmd->args && cmd->args[1])
		{
			t_token *current = builtin_token;
			int i = 1;
			while (cmd->args[i])
			{
				t_token *arg_token = malloc(sizeof(t_token));
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
		
		int ret = run_builtin(cmd->cmd, builtin_token, env_list);
		t_token *current = builtin_token;
		while (current)
		{
			t_token *next = current->next;
			free(current);
			current = next;
		}
		exit(ret);
	}
	if (cmd->cmd_path)
		execve(cmd->cmd_path, cmd->args, envp);
	else if (cmd->cmd)
		execve(cmd->cmd, cmd->args, envp);
	
	perror("execve failed");
	exit(127);
}

void	close_all_pipes(int pipe_fds[][2], int pipe_count)
{
	int i;
	
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
	int i;
	
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

void	setup_child_pipes(t_token_exc *cmd, int pipe_fds[][2], int cmd_index, int last_cmd_index)
{
	// Setup input (read from previous pipe or stdin)
	// Only set fd_in if it's not already set by redirection
	if (cmd->fd_in == 0)  // Only if no input redirection
	{
		if (cmd_index == 0)
			cmd->fd_in = 0;  // First command reads from stdin
		else
			cmd->fd_in = pipe_fds[cmd_index - 1][0];  // Read from previous pipe
	}
	
	// Setup output (write to next pipe or stdout)
	// Only set fd_out if it's not already set by redirection
	if (cmd->fd_out == 1)  // Only if no output redirection
	{
		if (cmd_index == last_cmd_index)
			cmd->fd_out = 1;  // Last command writes to stdout
		else
			cmd->fd_out = pipe_fds[cmd_index][1];  // Write to next pipe
	}
}

int	pipes(t_token **token, t_token_exc **command, t_env *env_list)
{
	int		count;
	int		(i), (j), (status), (child_status);
	int		pipe_fds[32][2];
	pid_t	pids[33];
	t_token_exc	*cmd_current;
	char	**envp;

	if (!token || !(*token) || !command || !(*command))
		return (0);
	
	count = count_cmd(command);
	if (count <= 1)
		return (0);
	cmd_current = *command;
	while (cmd_current)
	{
		path(&cmd_current);
		cmd_current = cmd_current->next;
	}
	envp = env_to_array(env_list);
	if (!envp)
		return (0);
	i = 0;
	while (i < count - 1)
	{
		if (pipe(pipe_fds[i]) == -1)
		{
			perror("pipe");
			close_all_pipes(pipe_fds, i);
			free_args(envp);
			return (0);
		}
		i++;
	}
	cmd_current = *command;
	i = 0;
	while (cmd_current && i < count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
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
			free_args(envp);
			return (0);
		}
		else if (pids[i] == 0)
		{
			setup_child_pipes(cmd_current, pipe_fds, i, count - 1);
			close_unused_pipes(pipe_fds, count - 1, i);
			execute_pipeline_command(cmd_current, envp, &env_list);
		}
		cmd_current = cmd_current->next;
		i++;
	}
	close_all_pipes(pipe_fds, count - 1);
	i = 0;
	status = 0;
	while (i < count)
	{
		waitpid(pids[i], &child_status, 0);
		if (i == count - 1 && WIFEXITED(child_status))
			status = WEXITSTATUS(child_status);
		i++;
	}
	free_args(envp);
	return (1);
}
