/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exe_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:48:25 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/24 12:57:11 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*create_env_node(const char *key, const char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_env));
	new->key = ft_strdup(key);
	if (!new->key)
	{
		free(new);
		return (NULL);
	}
	if (value)
	{
		new->value = ft_strdup(value);
		if (!new->value)
		{
			free(new->key);
			free(new);
			return (NULL);
		}
	}
	else
		new->value = NULL;
	return (new);
}

void	export_set_var(t_env **env_list, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (value)
			{
				if (tmp->value)
					free(tmp->value);
				tmp->value = ft_strdup(value);
			}
			return ;
		}
		tmp = tmp->next;
	}
	if (value)
	{
		tmp = create_env_node(key, value);
		if (!tmp)
			return ;
		tmp->next = *env_list;
		*env_list = tmp;
	}
}

void	export_print_sorted(t_env *env_list)
{
	t_env	*tmp;
	int		count;
	int		i;
	t_env	**arr;

	tmp = env_list;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	arr = NULL;
	if (count > 0)
		arr = (t_env **)malloc(sizeof(t_env *) * count);
	tmp = env_list;
	i = 0;
	while (i < count)
	{
		arr[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	export_print_sorted_helper(arr, count);
	free(arr);
}

void	execute_export_args(t_token *current, t_env **env_list)
{
	char	*eq;
	char	*key_backup;

	while (current)
	{
		eq = ft_strchr(current->value, '=');
		if (eq)
		{
			*eq = '\0';
			key_backup = ft_strdup(current->value);
			*eq = '=';
			export_set_var(env_list, key_backup, eq + 1);
			free(key_backup);
		}
		else
		{
			export_set_var(env_list, current->value, NULL);
		}
		current = current->next;
	}
}
