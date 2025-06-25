/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:17:49 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/25 15:18:14 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_cmd_child(t_token_exc **token_cmd, char **envp)
{
	int	fd;
	int	last;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	check_fd(token_cmd);
	if ((*token_cmd)->heredoc_file != NULL && (*token_cmd)->count_heredoc > 0)
	{
		last = (*token_cmd)->count_heredoc - 1;
		fd = open((*token_cmd)->heredoc_file[last], O_RDONLY);
		if (fd >= 0)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
	execve((*token_cmd)->cmd_path, (*token_cmd)->args, envp);
	perror("execve failed");
	free_env_array(envp);
	exit(0);
}

void	simple_cmd_parent(t_token_exc **token_cmd, char **envp, int status)
{
	int	j;
	int	sig;

	free_env_array(envp);
	if ((*token_cmd)->heredoc_file != NULL)
	{
		j = 0;
		while (j < (*token_cmd)->count_heredoc)
		{
			unlink((*token_cmd)->heredoc_file[j]);
			free((*token_cmd)->heredoc_file[j]);
			(*token_cmd)->heredoc_file[j] = NULL;
			j++;
		}
	}
	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			write(1, "Quit (core dumped)\n", 19);
	}
}
