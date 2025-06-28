/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:11:54 by akemmoun          #+#    #+#             */
/*   Updated: 2025/05/22 10:21:01 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_dot_count(t_token *token_tmp, char **s_ptr)
{
	int		count;
	char	*s;

	count = 0;
	if (!token_tmp || token_tmp->type != WORD)
		return (-1);
	*s_ptr = token_tmp->value;
	s = *s_ptr;
	while (*s)
	{
		if (*s == '.')
			count++;
		else
			return (count);
		s++;
	}
	return (count);
}

static void	ft_handle_dot_errors(char *s, int count)
{
	if (count == 1 || count == 2)
	{
		ft_putstr_fd("env: '", 1);
		ft_putstr_fd(s, 1);
		ft_putstr_fd("': Permission denied\n", 1);
	}
	else if (count > 2)
	{
		ft_putstr_fd("env: '", 1);
		ft_putstr_fd(s, 1);
		ft_putstr_fd("': No such file or directory\n", 1);
	}
}

static void	ft_count_dotes_env(t_token **token)
{
	t_token	*token_tmp;
	char	*s;
	int		count;

	if (!token)
		return ;
	token_tmp = (*token)->next;
	count = ft_get_dot_count(token_tmp, &s);
	if (count < 0)
		return ;
	ft_handle_dot_errors(s, count);
}

static void	handle_env_error_cases(t_token *token_tmp, t_env *env_list)
{
	if (ft_strncmp(token_tmp->value, "cd", 2) == 0)
	{
		ft_putstr_fd("env: '", 1);
		ft_putstr_fd(token_tmp->value, 1);
		ft_putstr_fd("': No such file or directory\n", 1);
	}
	else if (check_commande(token_tmp->value) == 4)
	{
		ft_putstr_fd("cd: cannot access '", 1);
		expander(token_tmp, env_list);
		ft_putstr_fd("': No such file or directory\n", 1);
	}
}

void	ft_env(t_token **token, t_env *env_list)
{
	t_token	*token_tmp;

	if ((!token) || (ft_strcmp((*token)->value, "env") != 0))
		return ;
	token_tmp = (*token)->next;
	if (!token_tmp)
	{
		get_env(env_list);
		return ;
	}
	handle_env_error_cases(token_tmp, env_list);
	ft_count_dotes_env(token);
}
