/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:50:59 by akemmoun          #+#    #+#             */
/*   Updated: 2025/05/16 14:05:14 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(char *value, t_env *env_list)
{
	char	*dollar;
	char	*var_name;
	char	*env_value;
	char	*expanded_value;
	char	*key;
	size_t	prefix_len;
	size_t	var_len;

	dollar = ft_strchr(value, '$');
	if (!dollar)
	{
		return (ft_strdup(value));
	}
	prefix_len = dollar - value;
	var_name = dollar + 1;
	var_len = 0;
	while (var_name[var_len] && (ft_isalnum(var_name[var_len])
			|| var_name[var_len] == '_'))
	{
		var_len++;
	}
	key = ft_substr(var_name, 0, var_len);
	env_value = get_env_value(env_list, key);
	free(key);
	expanded_value = malloc(prefix_len + ft_strlen(env_value) + ft_strlen(dollar
				+ var_len + 1) + 1);
	if (!expanded_value)
		return (NULL);
	ft_strlcpy(expanded_value, value, prefix_len + 1);
	ft_strlcat(expanded_value, env_value, prefix_len + ft_strlen(env_value)
		+ 1);
	ft_strlcat(expanded_value, var_name + var_len, prefix_len
		+ ft_strlen(env_value) + ft_strlen(var_name + var_len) + 1);
	return (expanded_value);
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		ft_putstr_fd(tokens->value, 1);
		tokens = tokens->next;
	}
}

t_token	*expander(t_token *token_list, t_env *env_list)
{
	t_token	*curr;
	char	*expanded;

	curr = token_list;
	while (curr)
	{
		if (curr->type == ARG)
		{
			if ((curr->quote == 0 || curr->quote == '"')
				&& ft_strchr(curr->value, '$'))
			{
				expanded = expand_variable(curr->value, env_list);
				free(curr->value);
				curr->value = expanded;
			}
		}
		curr = curr->next;
	}
	print_tokens(token_list);
	return (token_list);
}

t_token	*echo_expander(t_token *token_list, t_env *env_list, int fd)
{
	t_token	*curr;
	char	*expanded;

	curr = token_list;
	while (curr)
	{
		if (curr->type == ARG)
		{
			if ((curr->quote == 0 || curr->quote == '"')
				&& ft_strchr(curr->value, '$'))
			{
				expanded = expand_variable(curr->value, env_list);
				free(curr->value);
				curr->value = expanded;
				ft_putstr_fd(curr->value, fd);
				ft_putstr_fd("\n", fd);
			}
		}
		curr = curr->next;
	}
	return (token_list);
}
