/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:52:14 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/05/28 18:52:15 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_pwd(t_token **token)
{
	char	path[PATH_MAX];
	t_token	*token_tmp;

	if (!token || !(*token))
		return ;
	token_tmp = (*token);
	if (ft_strncmp(token_tmp->value, "pwd", 3) != 0)
		return ;
	if (getcwd(path, PATH_MAX) != NULL)
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd("Something is wrong :/\n", 1);
}