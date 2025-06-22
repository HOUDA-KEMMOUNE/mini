/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:24:49 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/22 09:51:59 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_count_args(t_token *token)
// {
// 	int(count), (flag);
// 	count = 0;
// 	flag = 0;
// 	while ((token != NULL) && (ft_strncmp(token->value, "|", 1) != 0))
// 	{
// 		if (token->type == WORD && token->type != FILE_NAME && flag == 1)
// 			count++;
// 		flag = 1;
// 		token = token->next;
// 	}
// 	return (count);
// }

int ft_count_args(t_token *token)
{
    int count = 0;
    while (token != NULL && ft_strncmp(token->value, "|", 1) != 0)
    {
        if (token->type == WORD && token->type != FILE_NAME)
            count++;
        token = token->next;
    }
    return count;
}

void	syntax_error(char *s)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	ft_putstr_fd(s, 1);
	ft_putstr_fd("\n", 1);
}

void	filename_node(t_token **token)
{
	while ((*token))
	{
		if ((*token)->type == REDIR_IN || (*token)->type == REDIR_OUT
			|| (*token)->type == APPEND)
		{
			if ((*token)->next == NULL)
				break ;
			(*token) = (*token)->next;
			if ((*token)->type == REDIR_IN || (*token)->type == REDIR_OUT
				|| (*token)->type == APPEND)
				return ;
			(*token)->type = FILE_NAME;
		}
		(*token) = (*token)->next;
	}
}

// void	command_node(t_token **token, t_token_exc **new)
// {
// 	char	**args_tmp;
// 	int		(count_args), (i), (flag);
// 	t_token *head;

// 	head = (*token);
// 	count_args = ft_count_args((*token));
// 	// printf("count_args -----------> %d\n", count_args);
// 	args_tmp = malloc((count_args + 1) * sizeof(char *));
// 	i = 0;
// 	flag = 0;
// 	while ((*token) && ft_strncmp((*token)->value, "|", 1) != 0)
// 	{
// 		// printf("HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH\n");
// 		if ((*token)->type == WORD)
// 		{
// 			if (flag == 0)
// 			{
// 				// printf("mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm\n");
// 				// (*new)->cmd = (*token)->value;
// 				(*token)->type = CMD;
// 			}
// 			else
// 			{
// 				(*token)->type = ARG;
// 				// printf("token->value ==== %s\n", (*token)->value);
// 				// printf("HJJJJJJJJJJJJJJJJJJJ\n");
// 			}
// 			args_tmp[i] = (*token)->value;
// 			i++;
// 			flag = 1;
// 		}
// 		(*token) = (*token)->next;
// 	}
// 	(*token) = head;
// 	args_tmp[i] = NULL;
// 	(*new)->args = args_tmp;
// }

void	command_node(t_token **token, t_token_exc **new)
{
	t_token	*head;
	char	**args_tmp;

	int count_args, i, flag;
	head = (*token);
	count_args = ft_count_args((*token));
	args_tmp = malloc((count_args + 1) * sizeof(char *));
	if (!args_tmp)
		return ; // handle allocation failure
	i = 0;
	flag = 0;
	while ((*token) && ft_strncmp((*token)->value, "|", 1) != 0)
	{
		if ((*token)->type == WORD)
		{
			if (flag == 0)
				(*token)->type = CMD;
			else
				(*token)->type = ARG;
			if (i < count_args) // protect against overflow
				args_tmp[i++] = (*token)->value;
			flag = 1;
		}
		(*token) = (*token)->next;
	}
	(*token) = head;
	args_tmp[i] = NULL;
	(*new)->args = args_tmp;
}

static void	tokens_exc_helper(t_token **token, t_token_exc **token_list)
{
	t_token		*head;
	t_token_exc	*new;
	t_token_exc	*temp;

	if (!token || !(*token))
		return ;
	head = (*token);
	new = malloc(sizeof(t_token_exc));
	if (!new)
		return ;
	new->cmd = (*token)->value;
	new->fd_in = 0;
	new->fd_out = 1;
	new->next = NULL;
	filename_node(token);
	command_node(&head, &new);
	if ((*token_list) == NULL)
		(*token_list) = new;
	else
	{
		temp = (*token_list);
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	// int i = 0;
	// while ((*token_list))
	// {
	// 	printf("(*token_list)->args[%d] --> %s\n", i, (*token_list)->args[i]);
	// 	i++;
	// 	(*token_list) = (*token_list)->next;
	// }
}

t_token_exc	*tokens_exc_handler(t_token *token)
{
	t_token_exc	*token_list;
	t_token		*token_tmp;

	if (!token)
		return (NULL);
	token_list = NULL;
	token_tmp = token;
	while (token_tmp != NULL)
	{
		// token_list->cmd =
		tokens_exc_helper(&token_tmp, &token_list);
		if (token_tmp == NULL)
			break ;
		token_tmp = token_tmp->next;
		if (token_tmp == NULL)
			break ;
	}
	return (token_list);
}
