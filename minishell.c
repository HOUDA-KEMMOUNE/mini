/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:32:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/05/30 11:58:16 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char		input[1024];
	ssize_t		readed;
	t_env 		*env_list;
	t_token 	*tokens;
	t_token_exc	*tokens_exec;
	t_echo		*echo_struct;
	//char	*line;

	(void)argc;
	(void)argv;
	env_list = create_env_list(envp);
	while (1)
	{
		ft_putstr_fd("minishell> ", 1);
		signal(SIGINT, handler_sigint);
		signal(SIGQUIT, SIG_IGN); //to ignore CTRL+'\'
		disable_sig();
		readed = read(0, input, sizeof(input) - 1);
		if (readed == 0)
		{
			ft_putstr_fd("\nexit\n", 1);
			exit(0);
		}
		else
			input[readed] = '\0'; // null-terminate

// Remove newline if present
		if (readed > 0 && input[readed - 1] == '\n')
    		input[readed - 1] = '\0';
		// if (!fgets(input, sizeof(input), stdin))
		// break;
		// // Remove trailing newline if any
		// size_t len = strlen(input);
		// if (len > 0 && input[len - 1] == '\n')
		// input[len - 1] = '\0';
		
		tokens = lexer(input);
		tokens_exec = tokens_exc_handler(tokens);
		if (tokens)
		{
			parsing(input, &tokens, &echo_struct, env_list);
			ft_append(&tokens);
			ft_pwd(&tokens);
			if (ft_strchr(tokens->value, '$'))
			{
				tokens = expander(tokens, env_list);
				ft_putstr_fd("\n", 1);
			}
			t_token *tmp = tokens;
			while (tmp)
			{
				printf("TOKEN: %s\n", tmp->value);
				tmp = tmp->next;
			}
			if (handle_builtin(tokens, env_list))
				continue;
		}
	}
}
