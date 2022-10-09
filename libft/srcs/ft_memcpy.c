/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:36:34 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:45:04 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* The memcpy() function copies n bytes from memory area src to memory area
dst.  If dst and src overlap, behavior is undefined.  Applications in which
dst and src might overlap should use memmove(3) instead.*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*tempdst;
	const unsigned char	*tempsrc;

	if (!dst && !src)
		return (NULL);
	i = 0;
	tempdst = (unsigned char *)dst;
	tempsrc = (const unsigned char *)src;
	while (i < n)
	{
		tempdst[i] = tempsrc[i];
		i++;
	}
	return (dst);
}
