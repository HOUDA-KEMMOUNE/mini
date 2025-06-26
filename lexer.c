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

void	word_case(char *input, int *i, t_token **token_list)
{
	int		start;
	char	*word;
	char	quote;

	quote = 0;
	if (input[*i] == '"' || input[*i] == '\'')
	{
		quote = input[*i];
		if (!is_quote_closed(input, quote, *i + 1))
		{
			print_error("Unclosed quote");
			(*i)++;
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
		while (input[*i] && input[*i] != ' ' && input[*i] != '\t'
			&& input[*i] != '|' && input[*i] != '>' && input[*i] != '<')
			(*i)++;
		word = ft_substr(input, start, *i - start);
		add_token(token_list, word, WORD, 0);
		free(word);
	}
}

void	add_type(t_token **token_list)
{
	static t_meta_char	arr[] = {{"|", PIPE}, {">", REDIR_OUT}, {"<", REDIR_IN},
	{">>", APPEND}, {"<<", HEREDOC}};
	t_token				*head;
	int					i;
	int					flag;

	i = 0;
	flag = 0;
	head = (*token_list);
	while ((*token_list))
	{
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
		i = 0;
		(*token_list) = (*token_list)->next;
	}
	(*token_list) = head;
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

t_token	*lexer(char *input)
{
	t_token	*token_list;
	int		i;

	i = 0;
	token_list = NULL;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '|' || input[i] == '>' || input[i] == '<'
			|| (input[i] == '>' && input[i + 1] == '>') || (input[i] == '<'
				&& input[i + 1] == '<'))
		{
			if ((input[i] == '>' && input[i + 1] == '>') || (input[i] == '<'
					&& input[i + 1] == '<'))
			{
				char_to_str(input[i], 1, &token_list);
				i++;
			}
			else
				char_to_str(input[i], 0, &token_list);
			i++;
		}
		else
			word_case(input, &i, &token_list);
	}
	return (token_list);
}

int	syntax_err_msg(t_token **token, t_token_exc **commande)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		(*commande)->fd_out);
	ft_putstr_fd((*token)->value, (*commande)->fd_out);
	ft_putstr_fd("'\n", (*commande)->fd_out);
	return (1);
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
}
