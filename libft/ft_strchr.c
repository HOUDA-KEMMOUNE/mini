/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:05:33 by akemmoun          #+#    #+#             */
/*   Updated: 2024/11/17 12:27:45 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;
	char	cc;

	i = 0;
	cc = (char) c;
	while (str[i])
	{
		if (str[i] == cc)
			return ((char *) &str[i]);
		i++;
	}
	if (cc == '\0')
		return ((char *) &str[i]);
	return (NULL);
}
