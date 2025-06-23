#include "minishell.h"

static int	cmp_env(t_env *a, t_env *b)
{
	return (ft_strcmp(a->key, b->key));
}

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
			if (tmp->value)
				free(tmp->value);
			if (value)
				tmp->value = ft_strdup(value);
			else
				tmp->value = NULL;
			return;
		}
		tmp = tmp->next;
	}
	tmp = create_env_node(key, value);
	if (!tmp)
		return;
	tmp->next = *env_list;
	*env_list = tmp;
}

void	export_print_sorted_helper(t_env **arr, int count)
{
	int	i, j;
	t_env	*swap;

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
	i = 0;
	while (i < count)
	{
		printf("declare -x %s", arr[i]->key);
		if (arr[i]->value)
			printf("=\"%s\"", arr[i]->value);
		printf("\n");
		i++;
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
