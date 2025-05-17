/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:04:13 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/05/16 14:16:25 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_token **token, t_env *env_list)
{
	t_token	*token_tmp;
	char	*expanded_path;

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

		// Expand variable in token_tmp->value
		expanded_path = expand_variable(token_tmp->value, env_list);
		ft_putstr_fd(expanded_path, 1);
		free(expanded_path);

		ft_putstr_fd("': No such file or directory\n", 1);
	}

	ft_count_dotes(token);
}
