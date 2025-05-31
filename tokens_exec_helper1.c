/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_exec_helper1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:07:55 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/05/31 09:07:57 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokens_exc_helper1(t_token_exc **new, t_token **token)
{
	// if (!new)
	// 	return ;
	// (void)new;
	(*new)->cmd = (*token)->value;
	(*new)->fd_in = 1;
	(*new)->fd_out = 0;
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
	printf("node22: cmd = %s\n", (*token_list)->cmd);
}
