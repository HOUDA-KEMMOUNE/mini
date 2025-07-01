/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:00:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/27 16:00:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_operators(char *input, int *i, t_token **token_list)
{
	if ((input[*i] == '>' && input[*i + 1] == '>') || (input[*i] == '<'
			&& input[*i + 1] == '<'))
	{
		handle_double_operator(input, i, token_list);
		(*i)++;
	}
	else
	{
		handle_single_operator(input, i, token_list);
		(*i)++;
	}
	return (0);
}

void	handle_redirection_tokens(t_token **token, t_token_exc **commande)
{
	(*token) = (*token)->next;
	if ((*token)->type == WORD)
		(*token)->type = FILE_NAME;
	else if (syntax_err_msg(&(*token), &(*commande)) == 1)
		return ;
}
