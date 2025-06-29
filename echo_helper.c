/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:28:54 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/29 22:30:09 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo_flag(char *s)
{
	int		i;

	if (!s || s[0] != '-')
		return (0);
	i = 1;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (i);
}

int	check_simple_echo(t_token **token, t_token_exc **command)
{
	t_token		*token_tmp;

	if (!token || !(*token) || !command || !(*command))
		return (0);
	token_tmp = (*token);
	if (token_tmp->next == NULL)
	{
		ft_putstr_fd("\n", (*command)->fd_out);
		return (0);
	}
	return (1);
}
