/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_support.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 16:15:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/28 16:15:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_err_msg(t_token **token, t_token_exc **commande)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		(*commande)->fd_out);
	ft_putstr_fd((*token)->value, (*commande)->fd_out);
	ft_putstr_fd("'\n", (*commande)->fd_out);
	return (1);
}

void	assign_token_type(t_token **token_list, t_meta_char *arr)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < 5)
	{
		if (strcmp((*token_list)->value, arr[i].value) == 0)
		{
			flag = 1;
			(*token_list)->type = arr[i].type;
		}
		i++;
	}
	if (flag == 0)
		(*token_list)->type = WORD;
}

void	char_to_str(char c, int n, t_token **token_list)
{
	char	str[3];

	if (n == 0)
	{
		str[0] = c;
		str[1] = '\0';
	}
	else if (n == 1)
	{
		str[0] = c;
		str[1] = c;
		str[2] = '\0';
	}
	add_token(token_list, str, PIPE, 0);
}
