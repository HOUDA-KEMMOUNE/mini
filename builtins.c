/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:30:43 by akemmoun          #+#    #+#             */
/*   Updated: 2025/05/29 16:48:56 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_builtin(t_token *tokens, t_env *env)
{
    if (!tokens || !tokens->value)
        return 0;

    if (ft_strcmp(tokens->value, "cd") == 0)
        return builtin_cd(token_to_args(tokens), env);

    if (ft_strcmp(tokens->value, "pwd") == 0)
    {
        ft_pwd(&tokens);
        return 1;
    }

    if (ft_strcmp(tokens->value, "env") == 0)
    {
        get_env(env);
        return 1;
    }

    return 0; // Not a builtin
}

int	count_args(t_token *token)
{
	int count = 0;

	while (token)
	{
		count++;
		token = token->next;
	}
	return count;
}

char	**token_to_args(t_token *token)
{
	int		count = count_args(token);
	char	**args = malloc(sizeof(char *) * (count + 1));
	int		i = 0;

	if (!args)
		return (NULL);
	while (token)
	{
		args[i++] = ft_strdup(token->value);
		token = token->next;
	}
	args[i] = NULL;
	return args;
}
