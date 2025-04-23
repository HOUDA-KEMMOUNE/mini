/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:50:59 by akemmoun          #+#    #+#             */
/*   Updated: 2025/04/23 20:19:17 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *expand_variable(char *value)
{
    char *dollar;
    char *var_name;
    char *env_value;
    char *expanded_value;
    size_t prefix_len;
	size_t var_len;

    dollar = ft_strchr(value, '$');
    if (!dollar)
        return (ft_strdup(value));

	prefix_len = dollar - value;
    var_name = dollar + 1;
    var_len = 0;
    while (var_name[var_len] && (ft_isalnum(var_name[var_len]) || var_name[var_len] == '_'))
        var_len++;

	env_value = getenv(var_name);
	if (!env_value)
		env_value = "";
    expanded_value = malloc(prefix_len + ft_strlen(env_value) + ft_strlen(var_name + var_len) + 1);

    if (!expanded_value)
        return NULL;

    ft_strlcpy(expanded_value, value, prefix_len + 1);
    ft_strlcat(expanded_value, env_value, prefix_len + ft_strlen(env_value) + 1);
    ft_strlcat(expanded_value, var_name + var_len, prefix_len + ft_strlen(env_value) + ft_strlen(var_name + var_len) + 1);
    
    return (expanded_value);
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