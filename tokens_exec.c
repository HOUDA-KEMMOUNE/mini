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
	while (token->next != NULL)
	{
		count++;
		token = token->next;
	}
	return (count);
}

static void	tokens_exc_helper(t_token **token, t_token_exc **token_list)
{
	t_token_exc	*token_list_tmp;
	t_token		*token_tmp;
	char		*tmp;
	char		**args_tmp;
	int			count_args;
	size_t		len;
	int			i;
	int			j;

	if (!token_list || !(*token_list)
		|| !token || !(*token))
		return ;
	token_list_tmp = (*token_list);
	token_tmp = (*token);
	i = 0;
	j = 0;
	count_args = ft_count_args(*token);
	token_list_tmp->args = malloc(count_args * (sizeof(char *)) + 1);
	// args_tmp = malloc(count_args * (sizeof(char *)) + 1);
	while ((token_tmp != NULL) && (ft_strncmp(token_tmp->value, "|", 1) != 0))
	{
		len = ft_strlen(token_tmp->value);
		args_tmp[j] = malloc(len);
		if (i == 0)
		{
			token_list_tmp->cmd = token_tmp->value;
			// printf("jj\n");
			printf("token_list_tmp->cmd --> %s\n", token_list_tmp->cmd);
			tmp = token_list_tmp->cmd;
		}
		else
		{
			token_list_tmp->value = token_tmp->value;
			tmp = token_list_tmp->value;
		}
		token_list_tmp->type = token_tmp->type;
		args_tmp[j] = tmp;
		j++;
		i++;
		token_list_tmp->args = args_tmp;
		token_tmp = token_tmp->next;
		printf("tmp --> %s\n", tmp);
	}
	if (ft_strncmp(token_tmp->value, "|", 1) == 0)
	{
		token_list_tmp->next = NULL;
	}
	else
	{
		printf("batbout\n");
		return ;
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
		token_tmp = token_tmp->next;
	}
	return (token_list);
}
