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

static void	ft_count_env(char *s, int *count)
{
	while (*s)
	{
		if (*s == '.')
			*count = *count + 1;
		else
			return ;
		s++;
	}
}

static void	ft_print_env_error(char *s, int count)
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

	count = 0;
	if (!token)
		return ;
	token_tmp = (*token)->next;
	if (!token_tmp || token_tmp->type != WORD)
		return ;
	s = token_tmp->value;
	ft_count_env(s, &count);
	ft_print_env_error(s, count);
}

static void	handle_env_errors(t_token *token_tmp, t_env *env_list)
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
	handle_env_errors(token_tmp, env_list);
	ft_count_dotes_env(token);
}
