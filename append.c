/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:38:02 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/22 17:32:11 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_append_count(t_token **token)
{
	t_token	*token_tmp;
	char	*input;
	int		count;

	if (!token || !(*token))
		return (-1);
	count = 0;
	token_tmp = (*token);
	while (token_tmp)
	{
		input = token_tmp->value;
		if (ft_strncmp(input, "<<", 2) == 0)
			count++;
		token_tmp = token_tmp->next;
	}
	return (count);
}

void	ft_append(t_token **token)
{
	t_token	*token_tmp;
	int		count;

	if (!token || !(*token))
		return ;
	token_tmp = (*token);
	count = check_append_count(token);
	if (count == -1)
		return ;
	if (ft_strncmp(token_tmp->value, "<<", 2) == 0)
		return ;
}
