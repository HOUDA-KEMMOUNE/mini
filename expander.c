/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:50:59 by akemmoun          #+#    #+#             */
/*   Updated: 2025/04/23 17:23:10 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_variable(char *value)
{
	char *dollar;
	char *var_name;
	char *env_value;

	dollar = ft_strchr(value, '$');

	if (!dollar)
		ft_strdup(value);
	var_name = dollar + 1;
	env_value = getenv(var_name);
	if (!env_value)
		ft_strdup("");
	return (ft_strdup(env_value));
}

t_token *expander(t_token *token_list)
{
	t_token *curr;
	char *expanded;

	curr = token_list;
	while (curr)
	{
		if (curr->type == WORD)
		{
			if ((curr->quote == 0 || curr->quote == '"') && ft_strchr(curr->value, '$'))
			{
				expanded = expand_variable(curr->value);
				free(curr->value);
				curr->value = expanded;
			}
			curr = curr->next;
		}
	}
	return (token_list);
}