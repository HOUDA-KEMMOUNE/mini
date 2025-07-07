/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:00:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/01 00:00:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_word_parts(char *input, int *i, char **word,
			int preserve_quotes)
{
	char	*part;
	char	*temp;

	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& is_not_delimiter(input[*i]))
	{
		part = process_word_part(input, i, word, preserve_quotes);
		if (!part)
			return (1);
		temp = ft_strjoin(*word, part);
		free(*word);
		free(part);
		*word = temp;
	}
	return (0);
}

int	handle_concatenated_word(char *input, int *i, t_token **token_list)
{
	char	*word;
	char	quote_type;
	int		has_single_quote;
	int		has_double_quote;
	int		preserve_quotes;

	word = ft_strdup("");
	scan_quote_types(input, i, &has_single_quote, &has_double_quote);
	quote_type = get_quote_strategy(has_single_quote, has_double_quote,
			&preserve_quotes);
	if (process_word_parts(input, i, &word, preserve_quotes))
		return (1);
	add_token(token_list, word, WORD, quote_type);
	free(word);
	return (0);
}

int	is_not_delimiter(char c)
{
	return (c != '|' && c != '>' && c != '<');
}

int	is_word_char(char c)
{
	return (c != '|' && c != '>' && c != '<' && c != '"' && c != '\'');
}
