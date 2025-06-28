/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_exec_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:03:38 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/04/24 10:03:44 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_echo_flag(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if ((s[i] == '-' && i == 0) || (s[i] == 'n' && i != 0))
			i++;
		else
			break ;
	}
	return (i);
}

int	check_simple_echo(t_token **token, t_token_exc **command)
{
	t_token		*token_tmp;

	if (!token || !(*token) || !command || !(*command))
		return (0);
	token_tmp = (*token);
	if (token_tmp->next == NULL)
	{
		ft_putstr_fd("\n", (*command)->fd_out);
		return (0);
	}
	return (1);
}

void	echo_helper(int *i, t_token_exc **command)
{
	t_token_exc	*command_tmp;
	char		**arg;
	int			i_tmp;
	static int	flag;

	if (!command || !(*command))
		return ;
	command_tmp = (*command);
	arg = command_tmp->args;
	i_tmp = *i;
	if ((i_tmp == 0 && ft_strncmp(arg[i_tmp], "echo", 4) == 0)
		|| (check_echo_flag(arg[i_tmp]) > 1 && flag == 0))
	{
		flag = 0;
		i_tmp++;
	}
	else
	{
		ft_putstr_fd(arg[i_tmp], (*command)->fd_out);
		if (arg[i_tmp + 1])
			ft_putstr_fd(" ", (*command)->fd_out);
		flag = 1;
		i_tmp++;
	}
	*i = i_tmp;
}

void	echo(t_token **token, t_token_exc **command)
{
	t_token		*token_tmp;
	t_token_exc	*command_tmp;
	char		**arg;
	int			i;

	if (!token || !(*token) || !command || !(*command))
		return ;
	token_tmp = (*token);
	command_tmp = (*command);
	if (ft_strncmp(command_tmp->cmd, "echo", 4) != 0)
		return ;
	if (check_simple_echo(token, command) == 0)
		return ;
	arg = command_tmp->args;
	i = 0;
	while (arg[i])
		echo_helper(&i, command);
	token_tmp = token_tmp->next;
	if (check_echo_flag(token_tmp->value) <= 1)
		ft_putstr_fd("\n", (*command)->fd_out);
}

int	echo_builtin(t_token *tokens, t_env **env_list)
{
	t_token		*current;
	int			newline;
	int			first_arg;

	(void)env_list;
	current = tokens->next; // Skip "echo"
	newline = 1;
	first_arg = 1;

	// Check for -n flag
	if (current && current->value && ft_strncmp(current->value, "-n", 2) == 0)
	{
		newline = 0;
		current = current->next;
	}

	// Print arguments, but skip redirection operators and filenames
	while (current)
	{
		// Skip redirection operators and their associated filenames
		if (current->type == REDIR_OUT || current->type == REDIR_IN || 
			current->type == APPEND || current->type == HEREDOC)
		{
			current = current->next; // Skip operator
			if (current)
				current = current->next; // Skip filename/delimiter
			continue;
		}
		
		// Skip filenames that follow redirection operators
		if (current->type == FILE_NAME)
		{
			current = current->next;
			continue;
		}

		// Print regular arguments
		if (current->type == WORD || current->type == ARG)
		{
			if (!first_arg)
				ft_putstr_fd(" ", 1);
			ft_putstr_fd(current->value, 1);
			first_arg = 0;
		}
		
		current = current->next;
	}

	if (newline)
		ft_putstr_fd("\n", 1);

	return (0);
}
