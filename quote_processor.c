/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_processor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:00:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/01 00:00:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_quotes_from_token(char *value, char quote_type)
{
	int		len;
	char	*result;
	int		i;
	int		j;

	if (!value || quote_type == 0)
		return (ft_strdup(value));
	len = ft_strlen(value);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] != quote_type)
			result[j++] = value[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

t_token	*process_quotes(t_token *token_list)
{
	t_token	*curr;
	char	*new_value;

	curr = token_list;
	while (curr)
	{
		if (curr->quote != 0)
		{
			new_value = remove_quotes_from_token(curr->value, curr->quote);
			if (new_value)
			{
				free(curr->value);
				curr->value = new_value;
			}
		}
		curr = curr->next;
	}
	return (token_list);
}
