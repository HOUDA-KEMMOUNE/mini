/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:52:14 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/25 14:07:59 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_token *tokens, t_env **env_list)
{
	char	path[PATH_MAX];

	(void)tokens;
	(void)env_list;
	if (getcwd(path, PATH_MAX) != NULL)
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		ft_putstr_fd("Something is wrong :/\n", 1);
	}
	return (0);
}
