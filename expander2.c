/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 00:00:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/27 00:00:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		ft_putstr_fd(tokens->value, 1);
		tokens = tokens->next;
	}
}

static int	should_skip_expansion(t_token *prev, t_token *curr)
{
	(void)curr;
	if (prev && prev->type == HEREDOC)
		return (1);
	return (0);
}

static void	expand_token_if_needed(t_token *curr, t_env *env_list)
{
	char	*expanded;

	if (curr->quote == 0 && (ft_strchr(curr->value, '\'')
			|| ft_strchr(curr->value, '"')))
	{
		expanded = expand_quote_aware(curr->value, env_list);
		free(curr->value);
		curr->value = expanded;
	}
	else if (curr->quote == '\'')
		return ;
	else if ((curr->quote == 0 || curr->quote == '"')
		&& ft_strchr(curr->value, '$'))
	{
		expanded = expand_all_variables(curr->value, env_list);
		free(curr->value);
		curr->value = expanded;
	}
}

t_token	*expander(t_token *token_list, t_env *env_list)
{
	t_token	*curr;
	t_token	*prev;

	curr = token_list;
	prev = NULL;
	while (curr)
	{
		if (should_skip_expansion(prev, curr))
		{
			curr = curr->next;
			if (curr)
				prev = curr;
			continue ;
		}
		expand_token_if_needed(curr, env_list);
		prev = curr;
		curr = curr->next;
	}
	return (token_list);
}
