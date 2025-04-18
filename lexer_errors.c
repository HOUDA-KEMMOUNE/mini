/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:32:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/04/13 17:14:19 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_quote_closed(char *input, char quote, int start)
{
	while (input[start])
	{
		if (input[start] == quote)
			return (1);
		start++;
	}
	return (0);
}

void print_error(char *msg)
{
	ft_putstr_fd("Lexer error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
}