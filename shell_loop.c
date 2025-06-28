/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 10:00:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/28 10:00:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_environment(char **envp, t_env **env_list)
{
	*env_list = create_env_list(envp);
	if (envp[0] == NULL)
		init_minimal_env(env_list);
}

int	handle_eof_input(char *line, t_shell_data *data)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		minishell_cleanup(data->env_list, data->tokens,
			data->tokens_exec);
		exit(0);
	}
	return (0);
}

void	run_shell_loop(t_shell_data *data)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, handler_sigint);
		signal(SIGQUIT, SIG_IGN);
		line = readline("\033[1;32mminishell>\033[0m ");
		handle_eof_input(line, data);
		if (handle_empty_input(&line))
			continue ;
		add_history(line);
		if (process_command_line(line, data))
			continue ;
	}
}
