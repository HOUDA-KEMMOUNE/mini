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

void	ft_data_init(t_echo	**echo_struct)
{
	(*echo_struct)->fd = 1;
	(*echo_struct)->file = NULL;
	(*echo_struct)->input = NULL;
	(*echo_struct)->msg = NULL;
}

void	check_first_token(t_token **token)
{
	t_token	*token_tmp;
	char	*first_token;
	char	tmp;
	int		len;

	if (!token)
		return ;
	token_tmp = (*token);
	first_token = token_tmp->value;
	len = ft_strlen(first_token);
	if (len == 1)
	{
		tmp = *first_token;
		if (tmp == '|')
		{
			write(1, "minishell: parse error near `|'", ft_strlen("minishell: parse error near `|'"));
			exit (1);
		}
		else if (tmp == '(')
		{
			write(1, "minishell: unclosed parenthesis `('", ft_strlen("minishell: unclosed parenthesis `('"));
			exit (1);
		}
		else if (tmp == 39)
		{
			write(1, "minishell: parse error near `\''", ft_strlen("minishell: unclosed parenthesis `('"));
			exit (1);
		}
	}
	else
		return ;
}	

void    parsing(char *input, t_token **token, t_echo **echo_struct)
{
	// char	*s;
	// t_echo echo_struct;
	// t_token	*token_tmp;

	write(1, "hhhhh\n", ft_strlen("hhhhh\n"));
	if (!input || !token)
		return ;
	// token_tmp = (*token);
	check_first_token(token);
	// if (token_tmp->value == '|')
	// {
	// 	write(1, "minishell: parse error near `|'", ft_strlen("minishell: parse error near `|'"));
	// 	exit (1);
	// }
	// else if (token_tmp->value == '(')
	// {
	// 	write(1, "minishell: unclosed parenthesis `('", ft_strlen("minishell: unclosed parenthesis `('"));
	// 	exit (1);
	// }
	// else if (token_tmp->value == 39)
	// {
	// 	write(1, "minishell: parse error near `\''", ft_strlen("minishell: unclosed parenthesis `('"));
	// 	exit (1);
	// }
	ft_data_init(echo_struct);
	ft_echo(token, echo_struct);
	ft_cd(token);
	ft_ls(token);
	ft_export(token);
	ft_unset(token);
	ft_env(token);
	ft_exit(token);
}
