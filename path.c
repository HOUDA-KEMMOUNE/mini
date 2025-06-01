/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:23:13 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/01 15:23:19 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(void)
{
	t_env *env;
	char	*tmp;

	env = *env_func();
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
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
	splited_path = ft_split(path, ':');
	return (splited_path);
}

void	path(t_token_exc **token_list)
{
	char	**splited_path;
	char	*new_cmd;

	splited_path = split_path();
	new_cmd = ft_strjoin("/", (*token_list)->cmd);
	//i need the access() function
	// while ()
}
