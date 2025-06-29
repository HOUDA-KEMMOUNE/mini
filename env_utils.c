/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:45:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/29 15:45:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	init_minimal_env(t_env **env_list)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)))
	{
		export_set_var(env_list, "PWD", cwd);
	}
	export_set_var(env_list, "SHLVL", "1");
}

int	env_builtin(t_token *tokens, t_env **env_list)
{
	(void)tokens;
	get_env(*env_list);
	return (0);
}
