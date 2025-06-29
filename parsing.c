/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:09:26 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/22 14:34:32 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_special_char(char tmp)
{
	if (tmp == '|')
	{
		write(1, "minishell: parse error near `|'\n",
			ft_strlen("minishell: parse error near `|'\n"));
		return (1);
	}
	else if (tmp == '(')
	{
		write(1, "minishell: unclosed parenthesis `('\n",
			ft_strlen("minishell: unclosed parenthesis `('\n"));
		return (1);
	}
	else if (tmp == ')')
	{
		write(1, "minishell: unclosed parenthesis `)'\n",
			ft_strlen("minishell: unclosed parenthesis `)'\n"));
		return (1);
	}
	else if (tmp == 39)
	{
		write(1, "minishell: parse error near `\''\n",
			ft_strlen("minishell: parse error near `\''\n"));
		return (1);
	}
	return (0);
}

void	check_first_token(t_token **token)
{
	t_token	*token_tmp;
	char	*first_token;
	int		len;

	if (!token)
		return ;
	token_tmp = (*token);
	first_token = token_tmp->value;
	len = ft_strlen(first_token);
	if (len == 1 && handle_special_char(*first_token))
		return ;
}

void	parsing(char *input, t_token **token,
		t_env *env_list)
{
	(void)env_list;
	if (!input || !token)
		return ;
	check_first_token(token);
	ft_export(token);
	ft_unset(token);
	ft_exit(token);
}
