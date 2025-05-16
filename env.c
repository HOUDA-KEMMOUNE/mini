/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:34:35 by akemmoun          #+#    #+#             */
/*   Updated: 2025/05/16 10:13:41 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_list(char **envp)
{
	t_env	*env_list;
	t_env	*new;
	char	*equal_sign;

	env_list = NULL;
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
			ft_lstadd_back(&env_list, new);
		}
		envp++;
	}
	return (env_list);
}