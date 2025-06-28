/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:00:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/28 16:00:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_handle_empty_cmd(t_echo *echo_struct_tmp)
{
	ft_putstr_fd("\n", echo_struct_tmp->fd);
}

int	echo_handle_n_flag(t_token **token_tmp)
{
	if (ft_strncmp((*token_tmp)->value, "-n", 2) == 0)
	{
		if ((*token_tmp)->next == NULL)
			return (1);
		(*token_tmp) = (*token_tmp)->next;
		return (1);
	}
	return (0);
}

void	echo_write_char_by_char(t_token *token_tmp, t_echo *echo_struct_tmp)
{
	char	*s;

	s = token_tmp->value;
	while (*s)
	{
		if ((ft_strncmp(s, ">", 1) == 0) || (ft_strncmp(s, ">>", 2) == 0))
			break ;
		write(echo_struct_tmp->fd, s, 1);
		s++;
	}
}
