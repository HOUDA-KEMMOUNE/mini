/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_exec_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:03:38 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/04/24 10:03:44 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_handle_redir_out(t_token *token_tmp, t_echo **echo_struct)
{
	token_tmp = token_tmp->next;
	(*echo_struct)->fd = open(token_tmp->value,
			O_CREAT | O_WRONLY | O_TRUNC, 0640);
}

static void	echo_handle_append(t_token *token_tmp, t_echo **echo_struct)
{
	token_tmp = token_tmp->next;
	(*echo_struct)->fd = open(token_tmp->value,
			O_CREAT | O_RDWR | O_APPEND, 0640);
}

static void	redir_out_append(t_token **token, t_echo **echo_struct)
{
	t_token	*token_tmp;

	if (!token || !(*token))
		return ;
	token_tmp = (*token);
	while (token_tmp)
	{
		if ((token_tmp->type == REDIR_OUT) || (token_tmp->type == APPEND))
		{
			if (token_tmp->type == REDIR_OUT)
				echo_handle_redir_out(token_tmp, echo_struct);
			else if (token_tmp->type == APPEND)
				echo_handle_append(token_tmp, echo_struct);
			if ((*echo_struct)->fd <= 0)
			{
				ft_putstr_fd("Sorry, We can't open this file :(\n", 1);
				exit(1);
			}
		}
		token_tmp = token_tmp->next;
	}
}

void	echo(t_token **token, t_echo **echo_struct, t_env *env_list)
{
	t_echo	*echo_struct_tmp;
	t_token	*token_tmp;
	t_token	*head;

	if ((!token) || (ft_strncmp((*token)->value, "echo", 4) != 0))
		return ;
	token_tmp = (*token);
	head = (*token)->next;
	echo_struct_tmp = (*echo_struct);
	redir_out_append(token, &echo_struct_tmp);
	if (ft_strncmp(token_tmp->value, "echo", 4) == 0)
		echo_process_main_logic(token, head, echo_struct_tmp, env_list);
}
