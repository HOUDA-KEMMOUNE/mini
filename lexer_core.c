/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:00:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/28 16:00:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_whitespace(char *input, int *i)
{
	while (input[*i] == ' ' || input[*i] == '\t')
		(*i)++;
}

int	is_operator(char *input, int i)
{
	return (input[i] == '|' || input[i] == '>' || input[i] == '<'
		|| (input[i] == '>' && input[i + 1] == '>') || (input[i] == '<'
			&& input[i + 1] == '<'));
}

int	process_token(char *input, int *i, t_token **token_list)
{
	if (is_operator(input, *i))
		return (process_operators(input, i, token_list));
	else
		return (word_case(input, i, token_list));
}

void	retype_lexer(t_token **token, t_token_exc **commande)
{
	int	i;

	if (!token || !(*token) || !commande || !(*commande))
		return ;
	i = 0;
	while ((*token))
	{
		if (((*token)->type == WORD) && (i == 0))
			(*token)->type = CMD;
		else if (((*token)->type == REDIR_IN) || ((*token)->type == REDIR_OUT)
			|| ((*token)->type == APPEND))
			handle_redirection_tokens(token, commande);
		else if ((*token)->type == WORD)
			(*token)->type = ARG;
		i++;
		(*token) = (*token)->next;
	}
}
