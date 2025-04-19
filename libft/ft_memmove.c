/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:17:26 by akemmoun          #+#    #+#             */
/*   Updated: 2024/11/15 16:36:26 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t	i;
	char	*tmp_src;
	char	*tmp_dest;

	if (!dest && !src)
		return (NULL);
	i = 0;
	tmp_dest = (char *) dest;
	tmp_src = (char *) src;
	if (tmp_src < tmp_dest)
	{
		while (len-- > 0)
			tmp_dest[len] = tmp_src[len];
	}
	else
	{
		while (i < len)
		{
			tmp_dest[i] = tmp_src[i];
			i++;
		}
	}
	return (dest);
}
