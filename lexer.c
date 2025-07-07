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
	return (handle_concatenated_word(input, i, token_list));
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
		skip_whitespace(input, &i);
		if (input[i] == '\0')
			break ;
		error = process_token(input, &i, &token_list);
	}
	if (error)
	{
		free_token_list(token_list);
		return (NULL);
	}
	return (token_list);
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
