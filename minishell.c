/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:32:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/15 15:07:35 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_type(t_token *list);
int	se_redirections(t_token **token)
{
	t_token	*token_tmp;

	token_tmp = (*token);
	while (token_tmp)
	{
		if (token_tmp->type == REDIR_IN || token_tmp->type == REDIR_OUT || token_tmp->type == APPEND || token_tmp->type == HEREDOC)
		{
			token_tmp = token_tmp->next;
			if (token_tmp == NULL)
				return (-1);
			if (token_tmp->type == REDIR_IN || token_tmp->type == REDIR_OUT || token_tmp->type == APPEND || token_tmp->type == HEREDOC)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
				ft_putstr_fd(token_tmp->value, 1);
				ft_putstr_fd("'\n", 1);
				return (0);
			}
		}
		token_tmp = token_tmp->next;
	}
	return (1);
}

// int	check_pipeline(t_token **token)
// {
// 	if (se_redout(token) <= 0)
// 		return (0);
// 	else
// 		return (1);
// }

int main(int argc, char **argv, char **envp)
{
	t_env 		*env_list;
	t_token 	*tokens;
	t_token_exc	*tokens_exec;
	t_echo		*echo_struct;
	char		*line;

	(void)argc;
	(void)argv;
	env_list = NULL;
	tokens = NULL;
	tokens_exec = NULL;
	echo_struct = NULL;
	line = NULL;
	env_list = create_env_list(envp);
	init_shlvl(env_list);
	while (1)
	{
		// print prompt
		signal(SIGINT, handler_sigint);
		signal(SIGQUIT, SIG_IGN); // to ignore CTRL+backslash
		disable_sig();
		//"\033[1;34mminishell>\033[0m "
		line = readline("\033[1;32mminishell>\033[0m "); // use readline to read input line
		// line = readline("minishell> "); // use readline to read input line
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			minishell_cleanup(env_list, tokens, tokens_exec, echo_struct);
			exit(0);
		}
		if (*line == '\0')
			{ free(line); continue; }
		add_history(line);
		tokens = lexer(line);
		add_type(&tokens);
		tokens_exec = tokens_exc_handler(tokens);

		if (tokens)
		{
			if (se_redirections(&tokens) <= 0)
				goto cleanup;
			parsing(line, &tokens, &echo_struct, env_list);
			tokens_exc_redio(tokens, &tokens_exec);

			if (is_builtin(&tokens_exec) == 1)
			{
				path(&tokens_exec);
				if (tokens_exec->cmd_path)
					simple_cmd(tokens, &tokens_exec);
				goto cleanup;
			}
			if (run_builtin(tokens->value, tokens, &env_list))
				goto cleanup;
		}
		cleanup:
		free(line);
		free_token_list(tokens);
		free_token_exc_list(tokens_exec);
		free_echo_struct(echo_struct);
		line = NULL;
		tokens = NULL;
		tokens_exec = NULL;
		echo_struct = NULL;
	}
}
