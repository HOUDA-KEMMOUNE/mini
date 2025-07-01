/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:50:59 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/22 17:33:30 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_exit_status_special(const char *value)
{
	const char	*dollar;
	size_t		prefix_len;
	size_t		total_len;
	char		*result;
	char		*exit_str;

	dollar = ft_strchr(value, '$');
	if (!dollar || dollar[1] != '?')
		return (NULL);
	exit_str = ft_itoa(*exit_status_func());
	if (!exit_str)
		return (NULL);
	prefix_len = dollar - value;
	total_len = prefix_len + ft_strlen(exit_str) + ft_strlen(dollar + 2) + 1;
	result = malloc(total_len);
	if (!result)
	{
		free(exit_str);
		return (NULL);
	}
	ft_strlcpy(result, value, prefix_len + 1);
	ft_strlcat(result, exit_str, total_len);
	ft_strlcat(result, dollar + 2, total_len);
	free(exit_str);
	return (result);
}

char	*build_expanded_string(const char *value, size_t prefix_len,
		const char *env_value, const char *suffix)
{
	char	*expanded_value;
	size_t	total_len;

	total_len = prefix_len + ft_strlen(env_value) + ft_strlen(suffix) + 1;
	expanded_value = malloc(total_len);
	if (!expanded_value)
		return (NULL);
	ft_strlcpy(expanded_value, value, prefix_len + 1);
	ft_strlcat(expanded_value, env_value, total_len);
	ft_strlcat(expanded_value, suffix, total_len);
	return (expanded_value);
}

char	*expand_variable(char *value, t_env *env_list)
{
	char	*dollar;
	char	*var_name;
	char	*env_value;
	char	*key;
	size_t	var_len;

	if (expand_exit_status_special(value))
		return (expand_exit_status_special(value));
	dollar = ft_strchr(value, '$');
	if (!dollar)
		return (ft_strdup(value));
	var_name = dollar + 1;
	key = extract_var_name(var_name, &var_len);
	if (var_len == 0)
		return (ft_strdup(value));
	env_value = get_env_value(env_list, key);
	if (!env_value)
		env_value = "";
	free(key);
	return (build_expanded_string(value, dollar - value, \
			env_value, var_name + var_len));
}
