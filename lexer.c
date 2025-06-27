/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:32:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/22 14:39:25 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token **head, char *value, t_token_type type, char quote)
{
	t_token	*new;
	t_token	*temp;

	(void)type;
	new = malloc(sizeof(t_token));
	if (!new)
		return ;
	ft_memset(new, 0, sizeof(t_token));
	new->value = ft_strdup(value);
	new->quote = quote;
	new->next = NULL;
	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

int	word_case(char *input, int *i, t_token **token_list)
{
	if (input[*i] == '"' || input[*i] == '\'')
		return (handle_quoted_word(input, i, token_list));
	else
	{
		handle_regular_word(input, i, token_list);
		return (0);
	}
}

void	add_type(t_token **token_list)
{
	static t_meta_char	arr[] = {{"|", PIPE}, {">", REDIR_OUT}, {"<", REDIR_IN},
	{">>", APPEND}, {"<<", HEREDOC}};
	t_token				*head;

	head = (*token_list);
	while ((*token_list))
	{
		assign_token_type(token_list, arr);
		(*token_list) = (*token_list)->next;
	}
	(*token_list) = head;
}

t_token	*lexer(char *input)
{
	t_token	*token_list;
	int		i;
	int		error;

	i = 0;
	token_list = NULL;
	error = 0;
	while (input[i] && !error)
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '\0')
			break ;
		if (input[i] == '|' || input[i] == '>' || input[i] == '<'
			|| (input[i] == '>' && input[i + 1] == '>') || (input[i] == '<'
				&& input[i + 1] == '<'))
			error = process_operators(input, &i, &token_list);
		else
			error = word_case(input, &i, &token_list);
	}
	if (error)
	{
		free_token_list(token_list);
		return (NULL);
	}
	return (token_list);
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
