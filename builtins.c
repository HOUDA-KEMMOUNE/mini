/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:30:43 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/22 17:32:25 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_built	*init_builtins(void)
{
	static t_built	builtins[] = {
	{"cd", cd},
	{"pwd", pwd},
	{"export", export_builtin_adapter},
	{"unset", unset},
	{"env", env_builtin},
	{"echo", echo_builtin},
	{NULL, NULL}
	};

	return (builtins);
}

int	run_builtin(char *cmd, t_token *tokens, t_env **env_list)
{
	t_built	*builtins;
	int		i;
	int		result;

	builtins = init_builtins();
	i = 0;
	while (builtins[i].cmd)
	{
		if (strcmp(cmd, builtins[i].cmd) == 0)
		{
			result = builtins[i].ptr(tokens, env_list);
			*exit_status_func() = result;
			return (result);
		}
		i++;
	}
	return (0);
}
