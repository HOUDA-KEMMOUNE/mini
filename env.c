/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:34:35 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/25 15:35:06 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**env_func(void)
{
	static t_env	*env;

	return (&env);
}

int	*exit_status_func(void)
{
	static int	exit_status;

	exit_status = 0;
	return (&exit_status);
}

t_env	*create_env_list(char **envp)
{
	t_env	*new;
	char	*equal_sign;

	*env_func() = NULL;
	while (*envp)
	{
		equal_sign = ft_strchr(*envp, '=');
		if (equal_sign)
		{
			new = malloc(sizeof(t_env));
			if (!new)
				return (NULL);
			ft_memset(new, 0, sizeof(t_env));
			new->key = ft_substr(*envp, 0, equal_sign - *envp);
			new->value = ft_strdup(equal_sign + 1);
			new->next = NULL;
			ft_envadd_back(env_func(), new);
		}
		envp++;
	}
	return (*env_func());
}
