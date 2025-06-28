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

char	*expand_pid_special(const char *value)
{
	const char	*dollar;
	char		pid_str[20];
	size_t		prefix_len;
	size_t		total_len;
	char		*result;

	dollar = strchr(value, '$');
	if (!dollar || dollar[1] != '$')
		return (NULL);
	snprintf(pid_str, sizeof(pid_str), "%d", getpid());
	prefix_len = dollar - value;
	total_len = prefix_len + strlen(pid_str) + strlen(dollar + 2) + 1;
	result = malloc(total_len);
	if (!result)
		return (NULL);
	strncpy(result, value, prefix_len);
	result[prefix_len] = '\0';
	strcat(result, pid_str);
	strcat(result, dollar + 2);
	return (result);
}

char	*extract_var_name(const char *var_start, size_t *var_len_ptr)
{
	size_t	var_len;

	var_len = 0;
	while (var_start[var_len] && (ft_isalnum(var_start[var_len])
			|| var_start[var_len] == '_'))
		var_len++;
	*var_len_ptr = var_len;
	return (ft_substr(var_start, 0, var_len));
}

char	*build_expanded_string(const char *value, size_t prefix_len,
		const char *env_value, const char *var_name)
{
	char	*expanded_value;
	size_t	total_len;

	total_len = prefix_len + ft_strlen(env_value) + ft_strlen(var_name) + 1;
	expanded_value = malloc(total_len);
	if (!expanded_value)
		return (NULL);
	ft_strlcpy(expanded_value, value, prefix_len + 1);
	ft_strlcat(expanded_value, env_value, total_len);
	ft_strlcat(expanded_value, var_name, total_len);
	return (expanded_value);
}

char	*expand_variable(char *value, t_env *env_list)
{
	char	*dollar;
	char	*var_name;
	char	*env_value;
	char	*key;
	size_t	var_len;

	if (expand_pid_special(value))
		return (expand_pid_special(value));
	dollar = ft_strchr(value, '$');
	if (!dollar)
		return (ft_strdup(value));
	var_name = dollar + 1;
	key = extract_var_name(var_name, &var_len);
	env_value = get_env_value(env_list, key);
	if (!env_value)
		env_value = "";
	free(key);
	return (build_expanded_string(value, dollar - value, \
			env_value, var_name + var_len));
}
