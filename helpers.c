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
	t_env *temp;

	if (!lst || !new)
		return;
	if (*lst == NULL)
	{
		*lst = new;
		return;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
