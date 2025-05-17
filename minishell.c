/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:32:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/05/17 10:44:28 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char input[1024];
	t_env *env_list;
	t_token *tokens;
	t_echo	*echo_struct;

	(void)argc;
	(void)argv;
	env_list = create_env_list(envp);
	while (1)
	{
		printf("minishell> ");
		if (!fgets(input, sizeof(input), stdin))
			break;

		// Remove trailing newline if any
		size_t len = strlen(input);
		if (len > 0 && input[len - 1] == '\n')
			input[len - 1] = '\0';

		tokens = lexer(input);
		if (tokens)
		{
			parsing(input, &tokens, &echo_struct, env_list);
			// Free token list here if needed
			if (ft_strchr(tokens->value, '$'))
			{
				tokens = expander(tokens, env_list);
				ft_putstr_fd("\n", 1);
			}
		}
	}
}
