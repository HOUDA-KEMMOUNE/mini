/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 00:00:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/01 00:00:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_quoted_content(char *input, int *i, char quote)
{
	int		start;
	char	*content;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	content = ft_substr(input, start, *i - start);
	if (input[*i] == quote)
		(*i)++;
	return (content);
}

static void	add_quote_to_word(char **word, char current_quote)
{
	char	quote_str[2];

	quote_str[0] = current_quote;
	quote_str[1] = '\0';
	*word = ft_strjoin_free(*word, quote_str);
}

static char	*wrap_with_quotes(char *part, char current_quote)
{
	char	*quoted_part;
	char	quote_str[2];

	quote_str[0] = current_quote;
	quote_str[1] = '\0';
	quoted_part = ft_strjoin(part, quote_str);
	free(part);
	return (quoted_part);
}

char	*handle_quoted_part(char *input, int *i, char **word,
			int preserve_quotes)
{
	char	current_quote;
	char	*part;

	current_quote = input[*i];
	if (!is_quote_closed(input, current_quote, *i + 1))
	{
		print_error("Unclosed quote");
		free(*word);
		return (NULL);
	}
	if (preserve_quotes)
		add_quote_to_word(word, current_quote);
	part = extract_quoted_content(input, i, current_quote);
	if (preserve_quotes)
		part = wrap_with_quotes(part, current_quote);
	return (part);
}

char	*process_word_part(char *input, int *i,
		char **word, int preserve_quotes)
{
	char	*part;

	if (input[*i] == '"' || input[*i] == '\'')
		part = handle_quoted_part(input, i, word, preserve_quotes);
	else
		part = extract_unquoted_content(input, i);
	return (part);
}
