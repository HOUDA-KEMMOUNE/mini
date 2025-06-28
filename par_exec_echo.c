/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_exec_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:03:38 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/04/24 10:03:44 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_helper(int *i, t_token_exc **command)
{
	t_token_exc	*command_tmp;
	char		**arg;
	int			i_tmp;

	if (!command || !(*command))
		return ;
	command_tmp = (*command);
	arg = command_tmp->args;
	i_tmp = *i;
	if ((i_tmp == 0 && ft_strncmp(arg[i_tmp], "echo", 4) == 0)
		|| (i_tmp == 1 && ft_strncmp(arg[i_tmp], "-n", 4) == 0))
		i_tmp++;
	else
	{
		ft_putstr_fd(arg[i_tmp], (*command)->fd_out);
		if (arg[i_tmp + 1])
			ft_putstr_fd(" ", (*command)->fd_out);
		i_tmp++;
	}
	*i = i_tmp;
}

void	echo(t_token **token, t_token_exc **command)
{
	t_token		*token_tmp;
	t_token_exc	*command_tmp;
	char		**arg;
	int			i;

	if (!token || !(*token) || !command || !(*command))
		return ;
	token_tmp = (*token);
	command_tmp = (*command);
	if (ft_strncmp(command_tmp->cmd, "echo", 4) != 0)
		return ;
	arg = command_tmp->args;
	i = 0;
	while (arg[i])
	{
		echo_helper(&i, command);
	}
	token_tmp = token_tmp->next;
	if (ft_strncmp(token_tmp->value, "-n", 2) != 0)
		ft_putstr_fd("\n", (*command)->fd_out);
}
