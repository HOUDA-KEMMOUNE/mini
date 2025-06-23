/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:03:42 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/22 14:36:50 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	export_print_sorted(t_env *env_list)
// {
// 	t_env	*tmp;
// 	int		count;
// 	int		i;
// 	t_env	**arr;
// 	int		j;
// 	t_env	*swap;
// 	int		k;

// 	tmp = env_list;
// 	count = 0;
// 	while (tmp)
// 	{
// 		count++;
// 		tmp = tmp->next;
// 	}
// 	arr = NULL;
// 	if (count > 0)
// 		arr = (t_env **)malloc(sizeof(t_env *) * count);
// 	tmp = env_list;
// 	i = 0;
// 	while (i < count)
// 	{
// 		arr[i] = tmp;
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	i = 0;
// 	while (i < count - 1)
// 	{
// 		j = 0;
// 		while (j < count - i - 1)
// 		{
// 			if (cmp_env(arr[j], arr[j + 1]) > 0)
// 			{
// 				swap = arr[j];
// 				arr[j] = arr[j + 1];
// 				arr[j + 1] = swap;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	k = 0;
// 	while (k < count)
// 	{
// 		printf("declare -x %s", arr[k]->key);
// 		if (arr[k]->value)
// 			printf("=\"%s\"", arr[k]->value);
// 		printf("\n");
// 		k++;
// 	}
// 	free(arr);
// }

// void	export_set_var(t_env **env_list, char *key, char *value)
// {
// 	t_env	*tmp;
// 	t_env	*new;

// 	tmp = *env_list;
// 	while (tmp)
// 	{
// 		if (ft_strcmp(tmp->key, key) == 0)
// 		{
// 			if (tmp->value)
// 				free(tmp->value);
// 			if (value)
// 				tmp->value = ft_strdup(value);
// 			else
// 				tmp->value = NULL;
// 			return ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	new = malloc(sizeof(t_env));
// 	if (!new)
// 		return ;
// 	ft_memset(new, 0, sizeof(t_env));
// 	new->key = ft_strdup(key);
// 	if (!new->key)
// 	{
// 		free(new);
// 		return ;
// 	}
// 	if (value)
// 		new->value = ft_strdup(value);
// 	else
// 		new->value = NULL;
// 	if (value && !new->value)
// 	{
// 		free(new->key);
// 		free(new);
// 		return ;
// 	}
// 	new->next = *env_list;
// 	*env_list = new;
// }

int	export_internal(t_token *tokens, t_env **env_list)
{
	t_token	*current;
	char	*eq;

	current = tokens->next;
	if (!current)
	{
		export_print_sorted(*env_list);
		return (0);
	}
	while (current)
	{
		eq = ft_strchr(current->value, '=');
		if (eq)
		{
			*eq = '\0';
			export_set_var(env_list, current->value, eq + 1);
			*eq = '=';
		}
		else
		{
			export_set_var(env_list, current->value, NULL);
		}
		current = current->next;
	}
	return (0);
}

// t_env	*export(t_token *tokens, t_env *env_list)
// {
// 	export_internal(tokens, &env_list);
// 	return (env_list);
// }

// int	export_wrapper(t_token *tokens, t_env **env_list)
// {
// 	t_env *new_head = export(tokens, *env_list); // pass current head
// 	if (new_head != *env_list)
// 		*env_list = new_head; // update the caller's pointer
// 	return (0);
// }

int	export_builtin_adapter(t_token *tokens, t_env **env_list)
{
	export_internal(tokens, env_list);
	return (0);
}
