/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:09:26 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/04/24 10:09:27 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_data_init(t_echo	*echo_struct)
{
	echo_struct->fd = 1;
	echo_struct->file = NULL;
	echo_struct->input = NULL;
	echo_struct->msg = NULL;
}

void    parsing(char *input, t_token **token)
{
	// char	*s;
	t_echo	echo_struct;

	if (!input || !token)
		return ;
	if (*input == '|')
	{
		write(1, "minishell: parse error near `|'", ft_strlen("minishell: parse error near `|'"));
		exit (1);
	}
	else if (*input == '(')
	{
		write(1, "minishell: unclosed parenthesis `('", ft_strlen("minishell: unclosed parenthesis `('"));
		exit (1);
	}
	else if (*input == 39)
	{
		write(1, "minishell: parse error near `\''", ft_strlen("minishell: unclosed parenthesis `('"));
		exit (1);
	}
	ft_data_init(&echo_struct);
	ft_echo(token, &echo_struct);
	ft_cd(token);
	ft_ls(token);
	ft_export(token);
	ft_env(token);
	ft_exit(token);
}
