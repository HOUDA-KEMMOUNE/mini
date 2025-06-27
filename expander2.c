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

t_token	*expander(t_token *token_list, t_env *env_list)
{
	t_token	*curr;
	char	*expanded;

	curr = token_list;
	while (curr)
	{
		if ((curr->quote == 0 || curr->quote == '"')
			&& ft_strchr(curr->value, '$'))
		{
			expanded = expand_variable(curr->value, env_list);
			free(curr->value);
			curr->value = expanded;
		}
		curr = curr->next;
	}
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
