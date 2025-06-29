/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:30:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/29 15:30:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_token_exc **token_list)
{
	if ((ft_strncmp((*token_list)->cmd, "echo", 4) == 0)
		|| (ft_strncmp((*token_list)->cmd, "cd", 2) == 0)
		|| (ft_strncmp((*token_list)->cmd, "pwd", 4) == 0)
		|| (ft_strncmp((*token_list)->cmd, "export", 6) == 0)
		|| (ft_strncmp((*token_list)->cmd, "unset", 5) == 0)
		|| (ft_strncmp((*token_list)->cmd, "env", 3) == 0)
		|| (ft_strncmp((*token_list)->cmd, "exit", 4) == 0))
		return (0);
	else
		return (1);
}

int	check_first_cmd(t_token_exc *token_list)
{
	char	*s;

	s = token_list->cmd;
	if (ft_strncmp(s, ">", 1) == 0 || ft_strncmp(s, ">>", 2) == 0
		|| ft_strncmp(s, "<", 1) == 0 || ft_strncmp(s, "<<", 2) == 0
		|| ft_strncmp(s, "./minishell", ft_strlen("./minishell")) == 0)
		return (0);
	else
		return (1);
}
