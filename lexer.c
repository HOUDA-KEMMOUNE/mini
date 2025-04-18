/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:32:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/04/13 17:19:14 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_token(t_token **head, char *value, t_token_type type)
{
	t_token *new;

	new = malloc (sizeof(t_token));
	if (!new)
		return ;
	
	new->value = ft_strdup(value);
	new->type = type;
	new->next = NULL;

	if (*head == NULL)
		*head = new;
	else
	{
		t_token *temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void word_case(char *input, int *i, t_token **token_list)
{
	int start;
	char *word;
	char quote;

	if (input[*i] == '"' || input[*i] == '\'')
	{
		quote = input[*i];
		if (!is_quote_closed(input, quote, *i + 1))
		{
			print_error("Unclosed quote");
			return ;
		}
		(*i)++;
		start = *i;
		while (input[*i] && input[*i] != quote)
			(*i)++;
		word = ft_substr(input, start, *i - start);
		add_token(token_list, word, WORD);
		free(word);
		if (input[*i] == quote)
			(*i)++;
	}
	else
	{
		start = *i;
		while (input[*i] && input[*i] != ' ' && input[*i] != '\t' && \
		input[*i] !='|' && input[*i] != '>' && input[*i] != '<')
			(*i)++;
		word = ft_substr(input, start, *i - start);
		add_token(token_list, word, WORD);
		free(word);
	}		
}

t_token *lexer(char *input)
{
	t_token *token_list;
	int i = 0;

	token_list = NULL;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '|')
			add_token(&token_list, "|", PIPE);
		else if (input[i] == '>')
		{
			if (input[i+1] == '>')
			{
				add_token(&token_list, ">>", APPEND);
				i += 2;
			}
			else 
			{
				add_token(&token_list, ">", REDIR_OUT);
				i++;
			}
		}
		else if (input[i] == '<')
		{
			if (input[i+1] == '<')
			{
				add_token(&token_list, "<<", HEREDOC);
				i += 2;
			}
			else 
			{
				add_token(&token_list, "<", REDIR_IN);
				i++;
			}
		}
		else
			word_case(input, &i, &token_list);
	}
	return (token_list);
}
