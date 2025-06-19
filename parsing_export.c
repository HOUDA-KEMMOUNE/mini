/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:12:13 by akemmoun          #+#    #+#             */
/*   Updated: 2025/05/14 13:12:15 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_notForbidden_char(char c, int is_first)
{
	if (is_first)
	{
		// First character: only letter or underscore
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
			return (1);
		else
			return (0);
	}
	else
	{
		// Other characters: letter, digit, or underscore
		if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
				&& c <= 'Z') || (c == '_'))
			return (1);
		else
			return (0);
	}
}

// static void    check_var(t_token **token)
// {
// 	char	*var;
// 	int		i;

// 	var = (*token)->value;
// 	i = 0;
// 	if ((var[i] == '_') || (var[i] >= 'a' && var[i] <= 'z')
// 		|| (var[i] >= 'A' && var[i] <= 'Z'))
// 		i++;
// 	else
// 	{
// 		ft_putstr_fd("export: not an identifier: ", 1);
// 		ft_putstr_fd(var, 1);
// 		ft_putstr_fd("\n", 1);
// 		return ;
// 	}
// 	while (var[i])
// 	{
// 		if (var[i] == '=')
// 		{
// 			ft_putstr_fd("export: `=': not a valid identifier\n", 1);
// 			return ;
// 		}
// 		else if (is_notForbidden_char(var[i]) == 0)
// 		{
// 			ft_putstr_fd("export: not an identifier: ", 1);
// 			ft_putstr_fd(var, 1);
// 			ft_putstr_fd("\n", 1);
// 			return ;
// 		}
// 		i++;
// 	}
// }

static void	check_var(t_token **token)
{
	char	*var;
	char	*eq;

	var = (*token)->value;
	eq = ft_strchr(var, '=');
	if (eq)
	{
		// Temporarily split at '='
		*eq = '\0';
	}
	// Check first character
	if (!is_notForbidden_char(var[0], 1))
	{
		ft_putstr_fd("export: `", 1);
		ft_putstr_fd(var, 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
		if (eq)
			*eq = '=';
		return ;
	}
	// Check remaining characters
	for (int i = 1; var[i]; i++)
	{
		if (!is_notForbidden_char(var[i], 0))
		{
			ft_putstr_fd("export: `", 1);
			ft_putstr_fd(var, 1);
			ft_putstr_fd("': not a valid identifier\n", 1);
			if (eq)
				*eq = '=';
			return ;
		}
	}
	if (eq)
		*eq = '=';
}

// void	ft_export(t_token **token)
// {
// 	t_token	*token_tmp;
// 	// char	*var;

// 	if ((!token) || (ft_strncmp((*token)->value, "export", 6) != 0))
// 		return ;
// 	token_tmp = (*token);
// 	token_tmp = token_tmp->next;
// 	if (token_tmp->next == NULL)
// 		return ;
// 	while (token_tmp)
// 	{
// 		check_var(&token_tmp);
// 		token_tmp = token_tmp->next;
// 	}
// 	return ;
// }

void	ft_export(t_token **token)
{
	t_token	*token_tmp;

	if (!token || !*token || !(*token)->value)
		return ;
	if (ft_strncmp((*token)->value, "export", 6) != 0)
		return ;
	token_tmp = (*token)->next;
	if (!token_tmp)
		return ;
	while (token_tmp)
	{
		check_var(&token_tmp);
		token_tmp = token_tmp->next;
	}
}
