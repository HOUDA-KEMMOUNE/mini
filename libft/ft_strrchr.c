/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:23:18 by akemmoun          #+#    #+#             */
/*   Updated: 2024/11/09 15:26:54 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int c)
{
	int		i;
	char	*last;
	char	cc;

	i = 0;
	last = NULL;
	cc = (char) c;
	while (str[i])
	{
		if (str[i] == cc)
			last = &str[i];
		i++;
	}
	if (cc == '\0')
		return (&str[i]);
	return (last);
}
