/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_exec_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 22:51:37 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/29 22:52:22 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_args(t_token **token, char **args_tmp, int count_args)
{
	int				i;
	int				flag;
	t_token_process	proc;

	if (!token || !(*token) || !args_tmp)
		return ;
	i = 0;
	flag = 0;
	proc.args_tmp = args_tmp;
	proc.i = &i;
	proc.count_args = count_args;
	proc.flag = &flag;
	while ((*token) && (*token)->type != PIPE)
	{
		process_token_type(token, &proc);
	}
	if (i < count_args)
		args_tmp[i] = NULL;
}

void	add_token_exc_to_list(t_token_exc **token_list, t_token_exc *new)
{
	t_token_exc	*temp;

	if (!token_list || !new)
		return ;
	if ((*token_list) == NULL)
	{
		(*token_list) = new;
		return ;
	}
	temp = (*token_list);
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	tokens_exc_helper(t_token **token, t_token_exc **token_list)
{
	t_token	*token_tmp;

	if (!token || !(*token) || !token_list)
		return ;
	token_tmp = (*token);
	while (token_tmp)
	{
		process_command_token(&token_tmp, token_list);
	}
	filename_node(token);
}

void	process_token_type(t_token **token, t_token_process *proc)
{
	if (!token || !(*token) || !proc)
		return ;
	if ((*token)->type == WORD)
	{
		if (*(proc->i) < proc->count_args)
			handle_word_token(token, proc->args_tmp, proc->i, proc->flag);
	}
	else if ((*token)->type == HEREDOC)
	{
		handle_heredoc_token(token);
		return ;
	}
	else if ((*token)->type == REDIR_IN || (*token)->type == REDIR_OUT || \
			(*token)->type == APPEND)
	{
		(*token) = (*token)->next;
		if ((*token))
			(*token) = (*token)->next;
		return ;
	}
	if (*token)
		(*token) = (*token)->next;
}
