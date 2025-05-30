/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:24:49 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/05/29 13:24:51 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tokens_exc_helper(t_token **token, t_token_exc **token_list)
{
	t_token_exc	*token_list_tmp;
	t_token		*token_tmp;
	char		*tmp;
	char		**args_tmp;
	int			i;
	int			j;

	if (!token_list || !(*token_list)
		|| !token || !(*token))
		return ;
	token_list_tmp = (*token_list);
	token_tmp = (*token);
	i = 0;
	j = 0;
	while ((token_tmp != NULL) && (token_tmp->value != "|"))
	{
		if (i == 0)
		{
			token_list_tmp->cmd = token_tmp->value;
			tmp = token_list_tmp->cmd;
		}
		else
		{
			token_list_tmp->value = token_tmp->value;
			tmp = token_list_tmp->value;
		}
		token_list_tmp->type = token_tmp->type;
		args_tmp[j] = tmp;
		j++;
		i++;
		token_tmp = token_tmp->next;
		token_list_tmp->args = args_tmp;
	}
}

t_token_exc *tokens_exc_handler(t_token *token)
{
	t_token_exc	*token_list;
	t_token		*token_tmp;
	int			i;
	int			j;
	char		*tmp;
	char		**args_tmp;
	
	if (!token)
		return (NULL);
	i = 0;
	j = 0;
	token_tmp = token;
	args_tmp = token_list->args;
	token_list->fd_in = 1;
	token_list->fd_out = 0;
	while (token_tmp != NULL)
	{
		if (ft_strncmp(token_tmp->value, "|", 1) == 0)
		{
			i = 0;
			j = 0;
			// break ;
		}
		else
		{
			if (i == 0)
			{
				token_list->cmd = token_tmp->value;
				tmp = token_list->cmd;
			}
			else
			{
				token_list->value = token_tmp->value;
				tmp = token_list->value;
			}
		}
		token_list->type = token_tmp->type;
		args_tmp[j] = tmp;
		j++;
		i++;
		token_tmp = token_tmp->next;
		token_list->args = args_tmp;
	}
	return (token_list);
}
