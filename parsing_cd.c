/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:04:13 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/04/24 10:04:16 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_token **token)
{
	t_token	*token_tmp;

	if ((!token) || (ft_strncmp((*token)->value, "cd", 2) != 0))
		return ;
	token_tmp = (*token);
	if (token_tmp->next == NULL)
		return ;
	token_tmp = token_tmp->next;
	if (check_commande(token_tmp->value) == 0)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(token_tmp->value, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		return ;
	}
	else if (check_commande(token_tmp->value) == 4)
	{
		ft_putstr_fd("cd: cannot access '", 1);
		expander(token_tmp);
		ft_putstr_fd("': No such file or directory\n", 1);
	}
	ft_count_dotes(token);
}
