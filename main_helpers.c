/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:00:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/28 10:00:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell_vars(t_shell_data *data)
{
	data->env_list = NULL;
	data->tokens = NULL;
	data->tokens_exec = NULL;
}

int	handle_empty_input(char **line)
{
	if (**line == '\0')
	{
		ft_putstr_fd("Command not found\n", 2);
		*exit_status_func() = 127;
		free(*line);
		return (1);
	}
	return (0);
}

void	cleanup_resources(char **line, t_token **tokens,
			t_token_exc **tokens_exec)
{
	free(*line);
	free_token_list(*tokens);
	free_token_exc_list(*tokens_exec);
	*line = NULL;
	*tokens = NULL;
	*tokens_exec = NULL;
}
