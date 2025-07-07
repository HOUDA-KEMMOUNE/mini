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

int	is_not_delimiter(char c)
{
	return (c != '|' && c != '>' && c != '<');
}

int	is_word_char(char c)
{
	return (c != '|' && c != '>' && c != '<' && c != '"' && c != '\'');
}

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

char	*extract_unquoted_content(char *input, int *i)
{
	int		start;
	char	*content;

	start = *i;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& is_word_char(input[*i]))
		(*i)++;
	content = ft_substr(input, start, *i - start);
	return (content);
}

void	scan_quote_types(char *input, int *i, int *has_single, int *has_double)
{
	int	start_pos;

	start_pos = *i;
	*has_single = 0;
	*has_double = 0;
	while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
		&& is_not_delimiter(input[*i]))
	{
		if (input[*i] == '\'')
			*has_single = 1;
		else if (input[*i] == '"')
			*has_double = 1;
		(*i)++;
	}
	*i = start_pos;
}

char	*process_word_part(char *input, int *i, char **word, int preserve_quotes)
{
	char	*part;
	char	current_quote;
	char	*quoted_part;
	char	quote_str[2];

	if (input[*i] == '"' || input[*i] == '\'')
	{
		current_quote = input[*i];
		if (!is_quote_closed(input, current_quote, *i + 1))
		{
			print_error("Unclosed quote");
			free(*word);
			return (NULL);
		}
		if (preserve_quotes)
		{
			quote_str[0] = current_quote;
			quote_str[1] = '\0';
			*word = ft_strjoin_free(*word, quote_str);
		}
		part = extract_quoted_content(input, i, current_quote);
		if (preserve_quotes)
		{
			quoted_part = ft_strjoin(part, quote_str);
			free(part);
			part = quoted_part;
		}
	}
	else
		part = extract_unquoted_content(input, i);
	return (part);
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
