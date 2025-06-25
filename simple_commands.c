/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:07:23 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/25 15:18:11 by akemmoun         ###   ########.fr       */
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
	int		status;

	env = *env_func();
	pid = fork();
	(void)token;
	if ((*token_cmd)->cmd_path == NULL)
		return ;
	envp = env_to_array(env);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pid == 0)
		simple_cmd_child(token_cmd, envp);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		simple_cmd_parent(token_cmd, envp, status);
	}
}
