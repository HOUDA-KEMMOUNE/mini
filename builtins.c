/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:30:43 by akemmoun          #+#    #+#             */
/*   Updated: 2025/05/31 18:46:07 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run_builtin(char *cmd, t_token *tokens, t_env *env)
{
    t_built arr[] = {
        {"cd", cd},
        {"pwd", pwd},
        //{"echo", echo},
        {NULL, NULL}
    };

    int i = 0;
    while (arr[i].cmd)
    {
        if (strcmp(cmd, arr[i].cmd) == 0)
            return arr[i].ptr(tokens, env); // run and return builtin's return value
        i++;
    }
    return 0; // not a builtin
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
