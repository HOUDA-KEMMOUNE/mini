/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:23:13 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/25 12:21:10 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(void)
{
	t_env	*env;
	char	*tmp;

	env = *env_func();
	tmp = NULL;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			tmp = env->value;
			break ;
		}
		env = env->next;
	}
	return (tmp);
}

char	**split_path(void)
{
	char	*path;
	char	**splited_path;

	path = find_path();
	printf("DEBUG: split_path - path found: %s\n", path ? path : "NULL");
	if (path == NULL || !*path)
		return (NULL);  // Return NULL when PATH is unset, don't use fallback
	splited_path = ft_split(path, ':');
	if (splited_path) {
		printf("DEBUG: split_path - directories:\n");
		for (int i = 0; splited_path[i]; i++) {
			printf("DEBUG:   [%d]: %s\n", i, splited_path[i]);
		}
	}
	return (splited_path);
}

int	is_builtin(t_token_exc **token_list)
{
	if ((ft_strncmp((*token_list)->cmd, "echo", 4) == 0)
		|| (ft_strncmp((*token_list)->cmd, "cd", 2) == 0)
		|| (ft_strncmp((*token_list)->cmd, "pwd", 4) == 0)
		|| (ft_strncmp((*token_list)->cmd, "export", 6) == 0)
		|| (ft_strncmp((*token_list)->cmd, "unset", 5) == 0)
		|| (ft_strncmp((*token_list)->cmd, "env", 3) == 0)
		|| (ft_strncmp((*token_list)->cmd, "exit", 4) == 0))
		return (0);
	else
		return (1);
}

int	check_first_cmd(t_token_exc *token_list)
{
	char	*s;

	s = token_list->cmd;
	if (ft_strncmp(s, ">", 1) == 0 || ft_strncmp(s, ">>", 2) == 0
		|| ft_strncmp(s, "<", 1) == 0 || ft_strncmp(s, "<<", 2) == 0
		|| ft_strncmp(s, "./minishell", ft_strlen("./minishell")) == 0)
		return (0);
	else
		return (1);
}

void	path(t_token_exc **token_list)
{
	char	**splited_path;
	char	*new_cmd;
	int		flag;

	splited_path = split_path();
	flag = 0;
	(*token_list)->cmd_path = NULL;
	
	// Handle absolute/relative paths even when PATH is unset
	if ((*token_list)->cmd && ft_strchr((*token_list)->cmd, '/'))
	{
		if (access((*token_list)->cmd, F_OK) == 0)
		{
			(*token_list)->cmd_path = ft_strdup((*token_list)->cmd);
			flag = 1;
		}
	}
	// Only search PATH if it exists and command doesn't contain '/'
	else if (splited_path)
	{
		new_cmd = ft_strjoin("/", (*token_list)->cmd);
		flag = set_cmd_path(splited_path, new_cmd, token_list);
		free(new_cmd);
	}
	
	if (splited_path)
		free_split_path(splited_path);
		
	if (flag == 0 && check_first_cmd(*token_list) == 1)
	{
		if (!(*token_list)->cmd || (*token_list)->cmd[0] == '\0')
			return ;
		print_cmd_error((*token_list)->cmd);
		*exit_status_func() = 127;
	}
}
