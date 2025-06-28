/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:32:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/22 09:55:30 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	se_redirections(t_token **token)
{
	t_token	*token_tmp;

	token_tmp = (*token);
	while (token_tmp)
	{
		if (token_tmp->type == REDIR_IN || token_tmp->type == REDIR_OUT
			|| token_tmp->type == APPEND || token_tmp->type == HEREDOC)
		{
			token_tmp = token_tmp->next;
			if (token_tmp == NULL)
				return (-1);
			if (token_tmp->type == REDIR_IN || token_tmp->type == REDIR_OUT
				|| token_tmp->type == APPEND || token_tmp->type == HEREDOC)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `",
					1);
				ft_putstr_fd(token_tmp->value, 1);
				ft_putstr_fd("'\n", 1);
				return (0);
			}
		}
		token_tmp = token_tmp->next;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell_data	data;

	(void)argc;
	(void)argv;
	init_shell_vars(&data);
	init_environment(envp, &data.env_list);
	run_shell_loop(&data);
	return (0);
}
