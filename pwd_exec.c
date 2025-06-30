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
	char	*pwd_env;

	(void)tokens;
	if (getcwd(path, PATH_MAX) != NULL)
	{
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
		return (0);
	}
	else
	{
		pwd_env = get_env_value(*env_list, "PWD");
		if (pwd_env)
		{
			ft_putstr_fd(pwd_env, 1);
			ft_putstr_fd("\n", 1);
			return (0);
		}
		ft_putstr_fd("pwd: error getting current directory\n", 2);
		return (1);
	}
}
