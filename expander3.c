/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 00:00:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/07 00:00:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_quoted_segment(char current_quote,
		char *segment, t_env *env_list)
{
	char	*expanded_segment;
	char	*result;

	if (current_quote == '"')
	{
		if (ft_strchr(segment, '$'))
		{
			expanded_segment = expand_all_variables(segment, env_list);
			result = ft_strdup(expanded_segment);
			free(expanded_segment);
		}
		else
			result = ft_strdup(segment);
	}
	else
		result = ft_strdup(segment);
	return (result);
}

static char	*process_unquoted_segment(char *segment, t_env *env_list)
{
	char	*expanded_segment;
	char	*result;

	if (ft_strchr(segment, '$'))
	{
		expanded_segment = expand_all_variables(segment, env_list);
		result = ft_strdup(expanded_segment);
		free(expanded_segment);
	}
	else
		result = ft_strdup(segment);
	return (result);
}

char	*handle_quoted_content(const char *value, int start,
		int len, char current_quote)
{
	(void)current_quote;
	return (ft_substr(value, start, len));
}

char	*handle_unquoted_content(const char *value, int *i,
		char *result, t_env *env_list)
{
	int		start;
	char	*segment;
	char	*processed;

	start = *i;
	while (value[*i] && value[*i] != '\'' && value[*i] != '"')
		(*i)++;
	segment = ft_substr(value, start, *i - start);
	processed = process_unquoted_segment(segment, env_list);
	result = ft_strjoin_free(result, processed);
	free(segment);
	free(processed);
	return (result);
}

char	*expand_all_variables(const char *value, t_env *env_list)
{
	char		*result;
	const char	*start;
	const char	*dollar;
	char		*temp;

	result = ft_strdup("");
	start = value;
	dollar = ft_strchr(start, '$');
	while (dollar)
	{
		temp = ft_substr(start, 0, dollar - start);
		result = ft_strjoin_free(result, temp);
		free(temp);
		if (is_special_var(dollar))
			start = expand_special_var(dollar, &result);
		else
			start = expand_normal_var(dollar, &result, env_list);
		dollar = ft_strchr(start, '$');
	}
	temp = ft_strdup(start);
	result = ft_strjoin_free(result, temp);
	free(temp);
	return (result);
}
