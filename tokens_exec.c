/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:24:49 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/25 13:36:06 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_args(t_token *token)
{
	int	count;

	count = 0;
	while (token != NULL && ft_strncmp(token->value, "|", 1) != 0)
	{
		if (token->type == WORD && token->type != FILE_NAME)
			count++;
		else if (token->type == REDIR_IN || token->type == REDIR_OUT || \
				token->type == APPEND || token->type == HEREDOC)
		{
			token = token->next;
			if (token)
				token = token->next;
			continue ;
		}
		token = token->next;
	}
	return (count);
}

void	syntax_error(char *s)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	ft_putstr_fd(s, 1);
	ft_putstr_fd("\n", 1);
}

void	filename_node(t_token **token)
{
	while ((*token))
	{
		if ((*token)->type == REDIR_IN || (*token)->type == REDIR_OUT
			|| (*token)->type == APPEND)
		{
			if ((*token)->next == NULL)
				break ;
			(*token) = (*token)->next;
			if ((*token)->type == REDIR_IN || (*token)->type == REDIR_OUT
				|| (*token)->type == APPEND)
				return ;
			(*token)->type = FILE_NAME;
		}
		(*token) = (*token)->next;
	}
}

void	command_node(t_token **token, t_token_exc **new)
{
	t_token	*head;
	char	**args_tmp;
	int		count_args;
	int		i;

	head = (*token);
	count_args = ft_count_args((*token));
	args_tmp = malloc((count_args + 1) * sizeof(char *));
	if (!args_tmp)
		return ;
	i = 0;
	while (i <= count_args)
		args_tmp[i++] = NULL;
	fill_args(token, args_tmp, count_args);
	(*token) = head;
	(*new)->args = args_tmp;
}

t_token_exc	*tokens_exc_handler(t_token *token)
{
	t_token_exc	*token_list;
	t_token		*token_tmp;

	if (!token)
		return (NULL);
	token_list = NULL;
	token_tmp = token;
	while (token_tmp != NULL)
	{
		tokens_exc_helper(&token_tmp, &token_list);
		if (token_tmp == NULL)
			break ;
		token_tmp = token_tmp->next;
		if (token_tmp == NULL)
			break ;
	}
	return (token_list);
}
