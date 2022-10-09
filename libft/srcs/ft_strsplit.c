/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 17:05:21 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:48:02 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Allocates (with malloc(3)) and returns an array of “fresh” strings
(all ending with ’\0’, including the array itself)
obtained by spliting s using the character c as a delimiter.
If the allocation fails the function returns NULL.*/

static int	ft_transpose_array(char const *s, char **array, int i, size_t len)
{
	if (len > 0)
	{
		array[i] = ft_strsub(s - len, 0, len);
		if (array[i])
			return (1);
		else
			return (0);
	}
	return (1);
}

static char	**ft_del_array(char **array, int i)
{
	while (i--)
		free (array[i]);
	free (array);
	return (NULL);
}

static char	**ft_assign_array(char **array, char const *s, char c)
{
	char	*start;
	int		i;
	int		words;

	i = 0;
	words = ft_count_words(s, c);
	while (i < words)
	{
		while (*s == c && *s)
			s++;
		start = (char *)s;
		while (*s != c && *s)
			s++;
		if (ft_transpose_array(s, array, i, s - start) == 0)
			return (ft_del_array(array, i - 1));
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		words;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	array = (char **)malloc(sizeof(*array) * (words + 1));
	if (!array)
		return (NULL);
	array = ft_assign_array(array, s, c);
	return (array);
}
