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

int	run_builtin(char *cmd, t_token *tokens, t_env **env_list)
{
	const t_built	builtins[] = {
	{"cd", cd},
	{"pwd", pwd},
	{"export", export_builtin_adapter},
	{"unset", unset},
	{NULL, NULL}
	};
	t_built			arr[5];
	int				i;

	i = 0;
	while (i < 5)
	{
		arr[i] = builtins[i];
		i++;
	}
	i = 0;
	while (arr[i].cmd)
	{
		if (strcmp(cmd, arr[i].cmd) == 0)
			return (arr[i].ptr(tokens, env_list));
		i++;
	}
	return (0);
}
