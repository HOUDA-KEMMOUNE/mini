/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 20:02:45 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/30 20:02:51 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

int	is_special_var(const char *dollar)
{
	return (dollar[1] == '?');
}

const char	*expand_special_var(const char *dollar, char **result)
{
	char	*exit_str;

	if (dollar[1] == '?')
	{
		exit_str = ft_itoa(*exit_status_func());
		*result = ft_strjoin_free(*result, exit_str);
		free(exit_str);
		return (dollar + 2);
	}
	return (dollar);
}

const char	*expand_normal_var(const char *dollar, \
								char **result, t_env *env_list)
{
	size_t	var_len;
	char	*var_name;
	char	*env_value;

	var_name = extract_var_name(dollar + 1, &var_len);
	if (var_len == 0)
	{
		*result = ft_strjoin_free(*result, "$");
		free(var_name);
		return (dollar + 1);
	}
	env_value = get_env_value(env_list, var_name);
	if (!env_value)
		env_value = "";
	*result = ft_strjoin_free(*result, env_value);
	free(var_name);
	return (dollar + 1 + var_len);
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
