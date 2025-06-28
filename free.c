/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:39:52 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/25 10:05:08 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

void	free_token_list(t_token *tok)
{
	t_token	*tmp;

	while (tok)
	{
		tmp = tok;
		tok = tok->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_token_exc_list(t_token_exc *cmd)
{
	t_token_exc	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
			free_args(cmd->args);
		if (cmd->cmd_path)
			free(cmd->cmd_path);
		if (cmd->file)
			free(cmd->file);
		free_heredoc_arrays(cmd);
		free(cmd);
		cmd = tmp;
	}
}

void	minishell_cleanup(t_env *env, t_token *tokens, t_token_exc *tokens_exec)
{
	free_env_list(env);
	free_token_list(tokens);
	free_token_exc_list(tokens_exec);
}
