/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:41:43 by akemmoun          #+#    #+#             */
/*   Updated: 2024/11/18 17:50:02 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dest_len;
	size_t	both_len;

	src_len = ft_strlen(src);
	if (dest == NULL && destsize == 0)
		return (src_len);
	dest_len = ft_strlen(dest);
	i = 0;
	j = dest_len;
	both_len = src_len + dest_len;
	if (destsize <= dest_len)
		return (destsize + src_len);
	while (src[i] && dest_len + i < destsize - 1)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (both_len);
}
