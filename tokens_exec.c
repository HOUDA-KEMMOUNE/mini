/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:24:49 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/05/29 13:24:51 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_args(t_token *token)
{
	int		count;

	count = 0;
	while ((token != NULL) && (ft_strncmp(token->value, "|", 1) != 0))
	{
		count++;
		token = token->next;
	}
	return (count);
}

static void	tokens_exc_helper(t_token **token, t_token_exc **token_list)
{
	char		**args_tmp;
	int			count_args;
	t_token_exc	*new;
	t_token_exc	*temp;
	int			i;

	if (!token || !(*token))
		return ;
	new = malloc (sizeof(t_token_exc));
	if (!new)
		return ;
	count_args = ft_count_args(*token);
	args_tmp = malloc((count_args + 1) * sizeof(char *));
	i = 0;
	new->cmd = (*token)->value;
	new->fd_in = 0;
	new->fd_out = 1;
	new->next = NULL;

	while (((*token) != NULL) &&
	(ft_strncmp((*token)->value, "|", 1) != 0))
	{
		args_tmp[i] = (*token)->value;
		i++;
		(*token) = (*token)->next;
	}
	args_tmp[i] = NULL;
	new->args = args_tmp;
	if ((*token_list) == NULL)
		(*token_list) = new;
	else
	{
		temp = (*token_list);
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	// printf("node: cmd = %s\n", (*token_list)->cmd);
	// printf("node: fd_in = %d\n", (*token_list)->fd_in);
	// i = 0;
	// while (i < count_args)
	// {
	// 	printf("arg[%d] -> %s\n", i, (*token_list)->args[i]);
	// 	i++;
	// }
	// printf("-------------------------------------------\n\n");
}

t_token_exc *tokens_exc_handler(t_token *token)
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
