/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:30:18 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/04/19 16:30:21 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_command(void)
{
	write(1, "ERROR: This is not a command :/-\n", ft_strlen("ERROR: This is not a command :/-\n"));
	exit (1);
}

void	print_echo_error(void)
{
	write(1, "minishell: syntax error near unexpected token `newline'\n", ft_strlen("minishell: syntax error near unexpected token `newline'\n"));
	exit (1);
}
