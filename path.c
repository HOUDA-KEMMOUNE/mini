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
			printf("%s\n", env->key);
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
	if (path == NULL || !*path)
		return (NULL);
	splited_path = ft_split(path, ':');
	return (splited_path);
}

static int	resolve_command_path(t_token_exc **token_list, char **splited_path)
{
	char	*new_cmd;
	int		flag;

	flag = 0;
	(*token_list)->cmd_path = NULL;
	if ((*token_list)->cmd && ft_strchr((*token_list)->cmd, '/'))
	{
		if (access((*token_list)->cmd, F_OK | X_OK) == 0)
		{
			(*token_list)->cmd_path = ft_strdup((*token_list)->cmd);
			flag = 1;
		}
	}
	else if (splited_path)
	{
		new_cmd = ft_strjoin("/", (*token_list)->cmd);
		flag = set_cmd_path(splited_path, new_cmd, token_list);
		free(new_cmd);
	}
	return (flag);
}

void	path(t_token_exc **token_list)
{
	char	**splited_path;
	int		flag;

	splited_path = split_path();
	flag = resolve_command_path(token_list, splited_path);
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
