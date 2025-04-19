/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:57:02 by akemmoun          #+#    #+#             */
/*   Updated: 2024/11/12 15:52:44 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (s[i] != c)
	{
		counter++;
		i++;
	}
	while (s[i])
	{
		if (s[i] != c && s[i - 1] == c)
			counter++;
		i++;
	}
	return (counter);
}

static void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free (array);
}

static char	*ft_strncpy(char *dest, char const *src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

static char	**ft_copy(char const *s, char c, int words, char **array)
{
	int			i;
	int			len;
	char const	*index;

	i = 0;
	while (i < words)
	{
		while (*s && *s == c)
			s++;
		index = s;
		len = 0;
		while (*s != c && *s)
		{
			len++;
			s++;
		}
		array[i] = (char *) malloc (sizeof(char) * (len + 1));
		if (!array[i])
			return (ft_free(array), NULL);
		ft_strncpy(array[i++], index, len);
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**array;

	if (!s)
		return (NULL);
	if (s[0] == '\0')
	{
		array = (char **) malloc (sizeof(char *));
		if (!array)
			return (NULL);
		array[0] = NULL;
		return (array);
	}
	words = count_words(s, c);
	array = (char **) malloc (sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	if (!(ft_copy(s, c, words, array)))
		return (NULL);
	return (array);
}
