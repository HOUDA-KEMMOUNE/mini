/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:08:45 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/04/24 10:08:46 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_count(char *s, int *count)
{
	while (*s)
	{
		if (*s == '.')
            *count = *count + 1;
		else
			return ;
		s++;
	}
}

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
		s = token_tmp->value;
		ft_count(s, &count);
	}
	else
		return ;
	if (count > 2)
	{
		ft_putstr_fd("ls: ", 1);
		ft_putstr_fd(s, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		exit (1);
	}
}

void	ft_cd(t_token **token)
{
	if ((!token) || (ft_strncmp((*token)->value, "ls", 2) != 0))
		return ;
	ft_count_dotes(token);
}
