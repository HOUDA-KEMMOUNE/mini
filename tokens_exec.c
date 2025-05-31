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

static int	ft_count_args(t_token *token)
{
	int		count;
	// int		i;

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
	int			i;

	if (!token_list || !(*token_list)
		|| !token || !(*token))
		return ;
	new = malloc (sizeof(t_token_exc));
	if (!new)
		return ;
	(*token_list)->cmd = (*token)->value;
	(*token_list)->fd_in = 1;
	(*token_list)->fd_out = 0;
	(*token_list)->next = NULL;
	printf("cmd --> %s\n", (*token_list)->cmd);
	count_args = ft_count_args(*token);
	args_tmp = malloc(count_args * sizeof(char *) + 1);
	i = 0;
	while (((*token) != NULL) &&
	(ft_strncmp((*token)->value, "|", 1) != 0))
	{
		args_tmp[i] = (*token)->value;
		i++;
		(*token) = (*token)->next;
	}
	args_tmp[i] = NULL;
	(*token_list)->args = args_tmp;
	if ((*token_list) == NULL)
		(*token_list) = new;
	else
	{
		t_token_exc *temp = (*token_list);
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

t_token_exc *tokens_exc_handler(t_token *token)
{
	t_token_exc	*token_list;
	t_token		*token_tmp;
	
	if (!token)
		return (NULL);
	token_list = malloc(sizeof(t_token_exc));
	token_tmp = token;
	while (token_tmp != NULL)
	{
		tokens_exc_helper(&token_tmp, &token_list);
		if (token_tmp == NULL)
			break ;
		token_tmp = token_tmp->next;
		if (token_tmp == NULL)
			break ;
		printf("token_tmp->value = %s\n", token_tmp->value);
	}
	return (token_list);
}
