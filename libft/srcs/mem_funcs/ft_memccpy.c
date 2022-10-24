/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:17:33 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:44:55 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* The memccpy() function copies bytes from string src to string dst.  If the
character c (as converted to an unsigned char) occurs in the string src,
the copy stops and a pointer to the byte after the copy of c in the string
dst is returned.  Otherwise, n bytes are copied, and a NULL pointer is
returned.

The source and destination strings should not overlap, as the behavior
undefined.*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*tempdst;
	const unsigned char	*tempsrc;

	if (!dst || !src)
		return (NULL);
	i = 0;
	tempdst = (unsigned char *)dst;
	tempsrc = (const unsigned char *)src;
	while (i < n)
	{
		if (tempsrc[i] == (unsigned char)c)
		{
			tempdst[i] = tempsrc[i];
			i++;
			return (dst + i);
		}
		tempdst[i] = tempsrc[i];
		i++;
	}
	return (NULL);
}
