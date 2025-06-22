/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:07:23 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/22 10:48:57 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_fd(t_token_exc **token_cmd)
{
	if ((*token_cmd)->fd_in != 0)
	{
		dup2((*token_cmd)->fd_in, 0);
		close((*token_cmd)->fd_in);
	}
	if ((*token_cmd)->fd_out != 1)
	{
		dup2((*token_cmd)->fd_out, 1);
		close((*token_cmd)->fd_out);
	}
}
int	env_size(t_env *env_list)
{
	int	size;

	size = 0;
	while (env_list)
	{
		size++;
		env_list = env_list->next;
	}
	return (size);
}

char	**env_to_array(t_env *env_list)
{
	char	**envp;
	char	*tmp;
	char	*tmp2;
	int		i;
	int		size;

	i = 0;
	size = env_size(env_list);
	envp = malloc((size + 1) * sizeof(char *));
	while (env_list)
	{
		tmp = ft_strjoin(env_list->key, "=");
		tmp2 = ft_strjoin(tmp, env_list->value);
		envp[i] = tmp2;
		free(tmp);
		i++;
		env_list = env_list->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	simple_cmd(t_token *token, t_token_exc **token_cmd)
{
	int		pid;
	t_env	*env;
	char	**envp;
	int		fd;

	env = *env_func();
	pid = fork();
	(void)token;
	if ((*token_cmd)->cmd_path == NULL)
		return ;
	envp = env_to_array(env);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN); // to ignore CTRL+backslash
	if (pid == 0)             // child
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL); // to ignore CTRL+backslash
		check_fd(token_cmd);
		if ((*token_cmd)->delimiter != NULL)
		{
			fd = open((*token_cmd)->delimiter, O_CREAT | O_EXCL | O_RDWR, 0600);
			if (fd >= 0)
			{
            	dup2(fd, STDIN_FILENO);
            	close(fd);
        	}
		}
		execve((*token_cmd)->cmd_path, (*token_cmd)->args, envp);
		perror("execve failed");
		free_env_array(envp);
		exit(1);
	}
	else if (pid > 0)
	{
		int status;
		waitpid(pid, &status, 0);
		free_env_array(envp);

		if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (sig == SIGINT)
				write(1, "\n", 1); // print newline (like bash)
			else if (sig == SIGQUIT)
				write(1, "Quit (core dumped)\n", 19); // print quit message
		}
	}
}
