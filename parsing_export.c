/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:12:13 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/26 11:30:52 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_notforbidden_char(char c, int is_first)
{
	if (is_first)
	{
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'))
			return (1);
		else
			return (0);
	}
	else
	{
		if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A'
				&& c <= 'Z') || (c == '_'))
			return (1);
		else
			return (0);
	}
}

static int	check_var_valid_char(char *var, char *eq)
{
	int	i;

	i = 1;
	while (var[i])
	{
		if (!is_notforbidden_char(var[i], 0))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(var, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			if (eq)
				*eq = '=';
			return (0);
		}
		i++;
	}
	return (1);
}

static void	check_var(t_token **token)
{
	char	*var;
	char	*eq;
	int		valid;

	var = (*token)->value;
	eq = ft_strchr(var, '=');
	if (eq)
		*eq = '\0';
	if (!var[0] || !is_notforbidden_char(var[0], 1))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd((*token)->value, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		if (eq)
			*eq = '=';
		return ;
	}
	valid = check_var_valid_char(var, eq);
	if (eq)
		*eq = '=';
}

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
