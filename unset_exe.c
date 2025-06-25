/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:05:09 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/25 14:11:45 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_env_var(t_env **env, const char *name)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (strcmp(curr->key, name) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	is_valid_unset_name(char *name)
{
	int	j;

	if (!is_notForbidden_char(name[0], 1))
		return (0);
	j = 1;
	while (name[j])
	{
		if (!is_notForbidden_char(name[j], 0))
			return (0);
		j++;
	}
	return (1);
}

int	unset(t_token *tokens, t_env **env_list)
{
	t_token	*arg;
	char	*name;

	arg = tokens->next;
	while (arg)
	{
		name = arg->value;
		if (!is_valid_unset_name(name))
		{
			fprintf(stderr, "unset: `%s': not a valid identifier\n", name);
			arg = arg->next;
			continue ;
		}
		unset_env_var(env_list, name);
		arg = arg->next;
	}
	return (0);
}
