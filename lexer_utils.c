/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:30:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/27 15:30:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quoted_word(char *input, int *i, t_token **token_list)
{
	int		start;
	char	*word;
	char	quote;

	quote = input[*i];
	if (!is_quote_closed(input, quote, *i + 1))
	{
		print_error("Unclosed quote");
		(*i)++;
		return (1);
	}
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	word = ft_substr(input, start, *i - start);
	add_token(token_list, word, WORD, quote);
	free(word);
	if (input[*i] == quote)
		(*i)++;
	return (0);
}

void	handle_regular_word(char *input, int *i, t_token **token_list)
{
	int		start;
	char	*word;

	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
		(*i)++;
	word = ft_substr(input, start, *i - start);
	add_token(token_list, word, WORD, 0);
	free(word);
}

void	handle_double_operator(char *input, int *i, t_token **token_list)
{
	char_to_str(input[*i], 1, token_list);
	(*i)++;
}

void	handle_single_operator(char *input, int *i, t_token **token_list)
{
	char_to_str(input[*i], 0, token_list);
}

char	get_quote_strategy(int has_single, int has_double, int *preserve)
{
	if (has_single && has_double)
	{
		*preserve = 1;
		return (0);
	}
	else if (has_single && !has_double)
	{
		*preserve = 0;
		return ('\'');
	}
	else if (has_double && !has_single)
	{
		*preserve = 0;
		return ('"');
	}
	else
	{
		*preserve = 0;
		return (0);
	}
}
