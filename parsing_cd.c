/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:04:13 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/05/31 17:44:56 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_token **token, t_env *env_list)
{
	t_token	*token_tmp;
	int		arg_count;
	t_token	*arg_ptr;

	arg_count = 0;
	(void)env_list;
	if ((!token) || (ft_strcmp((*token)->value, "cd") != 0))
		return ;
	token_tmp = (*token);
	if (token_tmp->next == NULL)
		return ;
	arg_ptr = token_tmp->next;
	while (arg_ptr && arg_ptr->type == WORD)
	{
		arg_count++;
		arg_ptr = arg_ptr->next;
	}
	if (arg_count > 1)
		return ;
	token_tmp = token_tmp->next;
	if (check_commande(token_tmp->value) == 0)
		return ;
	if (check_commande(token_tmp->value) == 4)
		return ;
	ft_count_dotes(token);
}
