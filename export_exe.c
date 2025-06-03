/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:03:42 by akemmoun          #+#    #+#             */
/*   Updated: 2025/05/19 22:04:35 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cmp_env(t_env *a, t_env *b)
{
	return (ft_strcmp(a->key, b->key));
}

static void	export_print_sorted(t_env *env_list)
{
	t_env	*tmp;
	int		count;
	int		i;
	t_env	**arr;
	int		j;
	t_env	*swap;
	int		k;

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
	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (cmp_env(arr[j], arr[j + 1]) > 0)
			{
				swap = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = swap;
			}
			j++;
		}
		i++;
	}
	k = 0;
	while (k < count)
	{
		printf("declare -x %s", arr[k]->key);
		if (arr[k]->value)
			printf("=\"%s\"", arr[k]->value);
		printf("\n");
		k++;
	}
	free(arr);
}

static void	export_set_var(t_env **env_list, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			if (value)
				tmp->value = ft_strdup(value);
			else
				tmp->value = NULL;
			return ;
		}
		tmp = tmp->next;
	}
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = *env_list;
	*env_list = new;
}

int export(t_token *tokens, t_env *env_list)
{
    t_token *current = tokens->next;

    // If no arguments, print environment sorted
    if (!current)
    {
        export_print_sorted(env_list);
        return 0;
    }

    // Otherwise, handle each argument
    while (current)
    {
        char *eq = ft_strchr(current->value, '=');
        if (eq)
        {
            *eq = '\0';
            export_set_var(&env_list, current->value, eq + 1);
            *eq = '=';
        }
        else
        {
            export_set_var(&env_list, current->value, NULL);
        }
        current = current->next;
    }
    return 0;
}
