/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:11:54 by akemmoun          #+#    #+#             */
/*   Updated: 2025/05/14 13:11:57 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_token **token)
{
	t_token	*token_tmp;

	if ((!token) || (ft_strncmp((*token)->value, "env", 3) != 0))
		return ;
	token_tmp = (*token);
	token_tmp = token_tmp->next;
	if (token_tmp != NULL)
		return ;
}
