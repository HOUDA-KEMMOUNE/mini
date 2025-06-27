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

int	syntax_err_msg(t_token **token, t_token_exc **commande)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		(*commande)->fd_out);
	ft_putstr_fd((*token)->value, (*commande)->fd_out);
	ft_putstr_fd("'\n", (*commande)->fd_out);
	return (1);
}

void	assign_token_type(t_token **token_list, t_meta_char *arr)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < 5)
	{
		if (strcmp((*token_list)->value, arr[i].value) == 0)
		{
			flag = 1;
			(*token_list)->type = arr[i].type;
		}
		i++;
	}
	if (flag == 0)
		(*token_list)->type = WORD;
}

void	char_to_str(char c, int n, t_token **token_list)
{
	char	str[3];

	if (n == 0)
	{
		str[0] = c;
		str[1] = '\0';
	}
	else if (n == 1)
	{
		str[0] = c;
		str[1] = c;
		str[2] = '\0';
	}
	add_token(token_list, str, PIPE, 0);
}
