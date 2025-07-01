/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 12:00:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/07/01 12:00:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric_string(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	count_args(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		if (current->type == WORD || current->type == ARG)
			count++;
		current = current->next;
	}
	return (count);
}

int	exit_builtin(t_token *tokens, t_env **env_list)
{
	t_token	*current;
	int		exit_code;
	int		arg_count;

	(void)env_list;
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 2);
	current = tokens->next;
	arg_count = count_args(current);
	if (arg_count == 0)
		exit(*exit_status_func());
	if (!is_numeric_string(current->value))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(current->value, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (arg_count > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_code = ft_atoi(current->value);
	exit(exit_code);
}
