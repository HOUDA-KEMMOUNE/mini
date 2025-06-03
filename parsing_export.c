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

int	is_notForbidden_char(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || (c == '_'))
		return (1); // l2omore ta7t saytara ✅
	else
		return (0); // forbidden character ❌
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

static void check_var(t_token **token)
{
    char *var = (*token)->value;
    char *eq = ft_strchr(var, '=');

    if (eq) {
        // Temporarily split at '='
        *eq = '\0';
    }

    if (!is_valid_identifier(var)) {
        ft_putstr_fd("export: `", 1);
        ft_putstr_fd(var, 1);
        ft_putstr_fd("': not a valid identifier\n", 1);
        if (eq) *eq = '='; // restore
        return;
    }

    if (eq) *eq = '='; // restore
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
