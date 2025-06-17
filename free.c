/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:39:52 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/14 12:28:31 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_env_list(t_env *env)
{
    t_env *tmp;
    while (env)
    {
        tmp = env->next;
        free(env->key);
        free(env->value);
        free(env);
        env = tmp;
    }
}

void free_echo_struct(t_echo *echo)
{
    if (!echo) return;
    free(echo->file);
    free(echo->input);
    free(echo->msg);
    free(echo);
}

void free_token_list(t_token *tok)
{
    t_token *tmp;
    while (tok)
	{
        tmp = tok;
        tok = tok->next;
        free(tmp->value);
        free(tmp);
    }
}

void free_token_exc_list(t_token_exc *cmd)
{
    t_token_exc *tmp;
    while (cmd)
	{
        tmp = cmd;
        cmd = cmd->next;
        if (tmp->args) free(tmp->args);
        free(tmp);
    }
}


void free_env_array(char **envp)
{
    int i;

    i = 0;
    if (!envp)
        return;
    while (envp[i])
        free(envp[i++]);
    free(envp);
}

void minishell_cleanup(t_env *env, t_token *tokens, t_token_exc *tokens_exec, t_echo *echo)
{
    free_env_list(env);
    free_token_list(tokens);
    free_token_exc_list(tokens_exec);
    free_echo_struct(echo);
}