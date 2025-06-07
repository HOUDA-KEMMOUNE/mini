/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:32:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/02 11:03:24 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_type(t_token *list);
void	se_redout(t_token **token)
{
	t_token	*token_tmp;

	token_tmp = (*token);
	while (token_tmp)
	{
		printf("token_tmp->value = %s\n", token_tmp->value);
		if (token_tmp->type == REDIR_IN || token_tmp->type == REDIR_OUT || token_tmp->type == APPEND || token_tmp->type == HEREDOC)
		{
			token_tmp = token_tmp->next;
			printf("token_tmp->value = %s\n", token_tmp->value);
			if (token_tmp == NULL)
				return ;
			if (token_tmp->type == REDIR_IN || token_tmp->type == REDIR_OUT || token_tmp->type == APPEND || token_tmp->type == HEREDOC)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
				ft_putstr_fd(token_tmp->value, 1);
				ft_putstr_fd("'\n", 1);
				return ;
			}
		}
		token_tmp = token_tmp->next;
	}
}

// void	se_redin(t_token **token)
// {
// 	t_token	*token_tmp;

// 	token_tmp = (*token);
// 	while (token_tmp)
// 	{
// 		if (token_tmp->type == REDIR_IN)
// 		{
// 			token_tmp = token_tmp->next;
// 			if (token_tmp == NULL)
// 				return ;
// 			if (token_tmp->type == REDIR_IN || token_tmp->type == REDIR_OUT || token_tmp->type == APPEND || token_tmp->type == HEREDOC)
// 			{
// 				ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
// 				ft_putstr_fd(token_tmp->value, 1);
// 				ft_putstr_fd("'\n", 1);
// 				return ;
// 			}
// 		}
// 		token_tmp = token_tmp->next;
// 	}
// }

// void	se_append(t_token **token)
// {
// 	t_token	*token_tmp;

// 	token_tmp = (*token);
// 	while (token_tmp)
// 	{
// 		if (token_tmp->type == APPEND)
// 		{
// 			token_tmp = token_tmp->next;
// 			if (token_tmp == NULL)
// 				return ;
// 			if (token_tmp->type == REDIR_IN || token_tmp->type == REDIR_OUT || token_tmp->type == APPEND || token_tmp->type == HEREDOC)
// 			{
// 				ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
// 				ft_putstr_fd(token_tmp->value, 1);
// 				ft_putstr_fd("'\n", 1);
// 				return ;
// 			}
// 		}
// 		token_tmp = token_tmp->next;
// 	}
// }

// void	se_heredoc(t_token **token)
// {
// 	t_token	*token_tmp;

// 	token_tmp = (*token);
// 	while (token_tmp)
// 	{
// 		if (token_tmp->type == HEREDOC)
// 		{
// 			token_tmp = token_tmp->next;
// 			if (token_tmp == NULL)
// 				return ;
// 			if (token_tmp->type == REDIR_IN || token_tmp->type == REDIR_OUT || token_tmp->type == APPEND || token_tmp->type == HEREDOC)
// 			{
// 				ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
// 				ft_putstr_fd(token_tmp->value, 1);
// 				ft_putstr_fd("'\n", 1);
// 				return ;
// 			}
// 		}
// 		token_tmp = token_tmp->next;
// 	}
// }

void	check_pipeline(t_token **token)
{
	se_redout(token);
	// se_redin(token);
	// se_append(token);
	// se_heredoc(token);
}

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
	init_shlvl(env_list);
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
		add_type(&tokens);
		// while (tokens)
		// {
			// 	printf("token->value = %s\n", tokens->value);
			// 	tokens = tokens->next;
			// }
		tokens_exec = tokens_exc_handler(tokens);
		if (tokens)
		{
			check_pipeline(&tokens);
			// print_type(tokens);
			parsing(line, &tokens, &echo_struct, env_list);
			// retype_lexer(&tokens, &tokens_exec);
			// ft_append(&tokens);
			tokens_exc_redio(tokens, &tokens_exec);
			// printf("fgfhfg\n");
			if (is_builtin(&tokens_exec) == 1)
			{
				path(&tokens_exec);
				if (tokens_exec->cmd_path)    // <-- Only call if command was found!
					simple_cmd(tokens, &tokens_exec);
				free(line);
				continue; //  continue after non-builtin (prevents running more logic)
			}
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
			if (run_builtin(tokens->value, tokens, env_list))
			{
				free(line);
				continue;
			}
		}
		free(line);
	}
}
