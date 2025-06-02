/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:07:23 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/01 15:07:24 by hkemmoun         ###   ########.fr       */
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
	int		size;

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
		i++;
		env_list = env_list->next; 
	}
	return (envp);
}

void	simple_cmd(t_token *token, t_token_exc **token_cmd)
{
	int	pid;
	t_env 	*env;
	char	**envp;
	
	env = *env_func();

	pid = fork();
	(void)token;
	// (void)token_cmd;
	// if (pid < 0)
	// {
	// 	perror("");
	// }
	if ((*token_cmd)->cmd_path == NULL)
		return ;
	envp = env_to_array(env);
	// return ;
	if (pid == 0) //child
	{
		check_fd(token_cmd);
		dprintf(2, "================== args ===============\n");
		for(int i =0;  (*token_cmd)->args[i]; i++)
			dprintf(2, "{%s} ",  (*token_cmd)->args[i]);
		dprintf(2, "\n");
		execve((*token_cmd)->cmd_path, (*token_cmd)->args, envp);
		perror("execve failed");
		free (envp);
		exit (0);
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
	}
}
