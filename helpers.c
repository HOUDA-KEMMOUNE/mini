/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:16:17 by akemmoun          #+#    #+#             */
/*   Updated: 2025/05/17 10:25:07 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*ptr_s1;
	unsigned char	*ptr_s2;

	if (!s1 || !s2)
		return (-1);
	ptr_s1 = (unsigned char *)s1;
	ptr_s2 = (unsigned char *)s2;
	i = 0;
	while (ptr_s1[i] || ptr_s2[i])
	{
		if (ptr_s1[i] != ptr_s2[i])
			return (ptr_s1[i] - ptr_s2[i]);
		i++;
	}
	return (0);
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	get_env(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
}

int	tokens_exc_redio(t_token *token, t_token_exc **token_list)
{
	t_token	*token_tmp;
	int		type;

	if (!token || !token_list || !(*token_list))
		return (0);
	token_tmp = token;
	while (token_tmp)
	{
		type = token_tmp->type;
		if (type == REDIR_OUT || type == APPEND || type == REDIR_IN)
		{
			if (handle_redir(token_tmp, token_list, type) == -1)
				return (-1);
		}
		token_tmp = token_tmp->next;
	}
	return (0);
}

void	handle_heredoc_token(t_token **token)
{
	if (!token || !(*token))
		return ;
	(*token) = (*token)->next;
	if ((*token) && ((*token)->type == DELIMITER
			|| (*token)->type == ARG || (*token)->type == CMD))
	{
		(*token) = (*token)->next;
		return ;
	}
}
