/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:32:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/01 13:58:12 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_env 		*env_list;
	t_token 	*tokens;
	t_token_exc	*tokens_exec;
	t_echo		*echo_struct;
	char		*line;

	(void)argc;
	(void)argv;
	env_list = create_env_list(envp);
	while (1)
	{
		// print prompt
		signal(SIGINT, handler_sigint);
		signal(SIGQUIT, SIG_IGN); // to ignore CTRL+backslash
		disable_sig();

		line = readline("minishell> "); // use readline to read input line
		if (!line)
		{
			ft_putstr_fd("exit\n", 1); // handle Ctrl+D (EOF)
			exit(0);
		}
		if (*line == '\0') // skip empty input
		{
			free(line);
			continue;
		}

		add_history(line); // save line in history

		tokens = lexer(line);
		tokens_exec = tokens_exc_handler(tokens);
		if (tokens)
		{
			parsing(line, &tokens, &echo_struct, env_list);
			ft_append(&tokens);
			tokens_exc_redio(tokens, &tokens_exec);
			// ft_pwd(&tokens);
			if (ft_strchr(tokens->value, '$'))
			{
				tokens = expander(tokens, env_list);
				ft_putstr_fd("\n", 1);
			}
			t_token *tmp = tokens;
			while (tmp)
			{
				// printf("TOKEN: %s\n", tmp->value);
				tmp = tmp->next;
			}
			// if (run_builtin(tokens->value, tokens, env_list))
			// {
			// 	free(line);
			// 	continue;
			// }
		}
		free(line);
	}
}
