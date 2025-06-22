/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:39:52 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/22 11:03:30 by akemmoun         ###   ########.fr       */
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

void	free_echo_struct(t_echo *echo)
{
	if (!echo)
		return ;
	free(echo->file);
	free(echo->input);
	free(echo->msg);
	free(echo);
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

// void free_str_array(char **arr)
// {
//     int i = 0;
//     if (!arr)
//         return;
//     while (arr[i])
//         free(arr[i++]);
//     free(arr);
// }

void free_str_array_shallow(char **arr)
{
    if (arr)
		free(arr);
}

void free_token_exc_list(t_token_exc *cmd)
{
    t_token_exc *tmp;
    while (cmd)
    {
        tmp = cmd->next;
		if (cmd->args) {
            int j = 0;
            while (cmd->args[j]) {
                // debug print:
                // printf("args[%d]=%p (%s)\n", j, (void*)cmd->args[j], cmd->args[j]);
                j++;
                if (j > 100) break; // prevent infinite loop!
            }
        }
        // Do NOT free strings inside args, just the array
        if (cmd->args)
            free_str_array_shallow(cmd->args);
        if (cmd->cmd_path)
            free(cmd->cmd_path);
        if (cmd->file)
            free(cmd->file);
        if (cmd->delimiter)
            free(cmd->delimiter);
        // If value/cmd are NOT strdup'd, do NOT free them here!
        free(cmd);
        cmd = tmp;
    }
}

void	free_env_array(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

void	minishell_cleanup(t_env *env, t_token *tokens, t_token_exc *tokens_exec,
		t_echo *echo)
{
	free_env_list(env);
	free_token_list(tokens);
	free_token_exc_list(tokens_exec);
	free_echo_struct(echo);
}
