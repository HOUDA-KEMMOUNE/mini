/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:34:35 by akemmoun          #+#    #+#             */
/*   Updated: 2025/05/29 11:13:26 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**env_func(void)
{
	static t_env *env;
	return(&env);
}

t_env	*create_env_list(char **envp)
{
	// t_env	*env_list;
	t_env	*new;
	char	*equal_sign;

	// env_list = NULL;

	while (*envp)
	{
		equal_sign = ft_strchr(*envp, '=');
		if (equal_sign)
		{
			new = malloc(sizeof(t_env));
			if (!new)
				return (NULL);
			new->key = ft_substr(*envp, 0, equal_sign - *envp);
			new->value = ft_strdup(equal_sign + 1);
			new->next = NULL;
			ft_envadd_back(env_func(), new);
		}
		envp++;
	}
	return (*env_func());
}

char *get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void get_env(t_env *env_list)
{
    t_env *tmp = env_list;
    while (tmp)
    {
        if (tmp->value)
        {
            ft_putstr_fd(tmp->key, 1);
            ft_putstr_fd("=", 1);
            ft_putstr_fd(tmp->value, 1);
            ft_putstr_fd("\n", 1);
        }
        tmp = tmp->next;
    }
}