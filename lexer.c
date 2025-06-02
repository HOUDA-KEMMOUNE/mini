/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:32:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/05/15 13:51:32 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token **head, char *value, t_token_type type, char quote)
{
	t_token *new;

	new = malloc (sizeof(t_token));
	if (!new)
		return ;
	
	new->value = ft_strdup(value);
	new->type = type;
	new->quote = quote;
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

void	word_case(char *input, int *i, t_token **token_list)
{
	int start;
	char *word;
	char quote;

	quote = 0;
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
		add_token(token_list, word, WORD, quote);
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
		add_token(token_list, word, WORD, 0);
		free(word);
	}
}

t_token *lexer(char *input)
{
	t_token *token_list;
	int i;

	i = 0;
	token_list = NULL;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '|')
		{
			add_token(&token_list, "|", PIPE, 0);
			i++;
		}
		else if (input[i] == '>')
		{
			if (input[i+1] == '>')
			{
				add_token(&token_list, ">>", APPEND, 0);
				i += 2;
			}
			else 
			{
				add_token(&token_list, ">", REDIR_OUT, 0);
				i++;
			}
		}
		else if (input[i] == '<')
		{
			if (input[i+1] == '<')
			{
				add_token(&token_list, "<<", HEREDOC, 0);
				i += 2;
			}
			else 
			{
				add_token(&token_list, "<", REDIR_IN, 0);
				i++;
			}
		}
		else
			word_case(input, &i, &token_list);
	}
	return (token_list);
}

int	syntax_err_msg(t_token **token, t_token_exc **commande)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", (*commande)->fd_out);
	ft_putstr_fd((*token)->value, (*commande)->fd_out);
	ft_putstr_fd("'\n", (*commande)->fd_out);
	return 1;
}
// void	check_cmd_type(t_token **token, t_token_exc **commande)
// {
// 	while ((*token))
// 	{
// 		if ((*token)->type = CMD)
// 		{

// 		}
// 	}
// }

void	retype_lexer(t_token **token, t_token_exc **commande)
{
	int		i;

	if (!token || !(*token) || !commande || !(*commande))
		return ;
	i = 0;
	while ((*token))
	{
		if (((*token)->type == WORD) && (i == 0))
			(*token)->type = CMD;
		else if (((*token)->type == REDIR_IN) || ((*token)->type == REDIR_OUT) || ((*token)->type == APPEND))
		{
			(*token) = (*token)->next;
			if ((*token)->type == WORD)
				(*token)->type = FILE_NAME;
			else if (syntax_err_msg(&(*token), &(*commande)) == 1)
				return ;
		}
		else if ((*token)->type == WORD)
			(*token)->type = ARG;
		i++;
		(*token) = (*token)->next;
	}
	// check_cmd_type(token, commande);
}
