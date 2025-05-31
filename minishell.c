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
		// input[readed] = '\0'; // null-terminate
		// Remove newline if present
		if (readed > 0 && input[readed - 1] == '\n')
    		input[readed - 1] = '\0';
		tokens = lexer(input);
		tokens_exec = tokens_exc_handler(tokens);
		// printf("node: cmd = %s\n", tokens_exec->cmd);
		while (tokens_exec)
		{
			printf("node: cmd = %s\n", tokens_exec->cmd);
			int i = 0;
			int	count_args = ft_count_args(tokens);
			while (i < count_args)
			{
				printf("arg[%d] -> %s\n", i, tokens_exec->args[i]);
				i++;
			}
			printf("-------------------------------------------\n\n");
			tokens_exec = tokens_exec->next;
		}
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
			// t_token *tmp = tokens;
			// while (tmp)
			// {
			// 	printf("TOKEN: %s\n", tmp->value);
			// 	tmp = tmp->next;
			// }
			// if (handle_builtin(tokens, env_list))
			// 	continue;
		}
	}
}
