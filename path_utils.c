/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:07:14 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/25 12:22:14 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split_path(char **splited_path)
{
	int	i;

	i = 0;
	while (splited_path && splited_path[i])
	{
		free(splited_path[i]);
		i++;
	}
	free(splited_path);
}

int	set_cmd_path(char **splited_path, char *new_cmd, t_token_exc **token_list)
{
	char	*tmp;
	int		i;

	i = 0;
	while (splited_path[i])
	{
		tmp = ft_strjoin(splited_path[i], new_cmd);
		if (access(tmp, F_OK) == 0)
		{
			(*token_list)->cmd_path = tmp;
			return (1);
		}
		free(tmp);
		i++;
	}
	return (0);
}

void	print_cmd_error(const char *cmd)
{
	struct stat	st;

	if (!cmd || cmd[0] == 0)
		return ;
	if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
		printf("minishell: %s: Is a directory\n", cmd);
	else
		printf("minishell: %s: No such file or directory\n", cmd);
}
