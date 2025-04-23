/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:49:59 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/04/23 18:50:00 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_count_dotes(t_token **token)
{
	t_token *token_tmp;
	char	*s;
	int		count;

	if ((!token))
		return ;
	count = 0;
	token_tmp = (*token);
	token_tmp = token_tmp->next;
	if (token_tmp->type == WORD)
	{
		s = token_tmp;
		while (*s)
		{
			if (*s == '.')
				count++;
			else
				break ;
		}
	}
	else
		return ;
	if (count > 2)
	{
		ft_putstr_fd("cd: ", 1);
		ft_putstr_fd(token_tmp, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		exit (1);
	}
}

void	ft_cd(t_token **token)
{
	if ((!token) || (ft_strncmp((*token)->value, "cd", 2) != 0))
		return ;
	ft_count_dotes(token);
}
