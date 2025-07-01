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

static char	*extract_quoted_content(char *input, int *i, char quote)
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

static char	*extract_unquoted_content(char *input, int *i)
{
	int		start;
	char	*content;

	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& input[*i] != '|' && input[*i] != '>' && input[*i] != '<'
		&& input[*i] != '"' && input[*i] != '\'')
		(*i)++;
	content = ft_substr(input, start, *i - start);
	return (content);
}

static char	*process_word_part(char *input, int *i, char **word)
{
	char	*part;
	char	current_quote;

	if (input[*i] == '"' || input[*i] == '\'')
	{
		current_quote = input[*i];
		if (!is_quote_closed(input, current_quote, *i + 1))
		{
			print_error("Unclosed quote");
			free(*word);
			return (NULL);
		}
		part = extract_quoted_content(input, i, current_quote);
	}
	else
		part = extract_unquoted_content(input, i);
	return (part);
}

int	handle_concatenated_word(char *input, int *i, t_token **token_list)
{
	char	*word;
	char	*temp;
	char	*part;
	char	quote_type;

	word = ft_strdup("");
	quote_type = 0;
	if (input[*i] == '"' || input[*i] == '\'')
		quote_type = input[*i];
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
	{
		part = process_word_part(input, i, &word);
		if (!part)
			return (1);
		temp = ft_strjoin(word, part);
		free(word);
		free(part);
		word = temp;
	}
	add_token(token_list, word, WORD, quote_type);
	free(word);
	return (0);
}
