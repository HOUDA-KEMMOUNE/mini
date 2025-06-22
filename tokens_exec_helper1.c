/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_exec_helper1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:07:55 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/22 14:35:01 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokens_exc_helper1(t_token_exc **new, t_token **token)
{
	(*new)->cmd = (*token)->value;
	(*new)->fd_in = 0;
	(*new)->fd_out = 1;
	(*new)->next = NULL;
}

void	tokens_exc_helper2(t_token_exc **new, t_token_exc **token_list)
{
	t_token_exc	*temp;

	if ((*token_list) == NULL)
		(*token_list) = (*new);
	else
	{
		temp = (*token_list);
		while (temp->next)
			temp = temp->next;
		temp->next = (*new);
	}
}

void	tokens_exc_redio(t_token *token, t_token_exc **token_list)
{
	t_token	*token_tmp;

	if (!token || !token_list || !(*token_list))
		return ;
	token_tmp = token;
	while (token_tmp)
	{
		if (ft_strncmp((*token_list)->cmd, "echo", 4) == 0)
			return ;
		if (token_tmp->type == REDIR_OUT)
		{
			token_tmp = token_tmp->next;
			(*token_list)->file = ft_strdup(token_tmp->value);
			(*token_list)->fd_out = open(token_tmp->value,
					O_CREAT | O_WRONLY | O_TRUNC, 0640);
		}
		else if (token_tmp->type == APPEND)
		{
			token_tmp = token_tmp->next;
			(*token_list)->file = ft_strdup(token_tmp->value);
			(*token_list)->fd_out = open(token_tmp->value,
					O_CREAT | O_WRONLY | O_APPEND, 0640);
		}
		else if (token_tmp->type == REDIR_IN)
		{
			token_tmp = token_tmp->next;
			(*token_list)->file = ft_strdup(token_tmp->value);
			if (open(token_tmp->value, O_RDONLY) < 0)
			{
				ft_putstr_fd("minishell: ", 1);
				perror((*token_list)->file);
			}
		}
		token_tmp = token_tmp->next;
	}
}
