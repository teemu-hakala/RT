/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:34:02 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:45:20 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* The memmove() function copies len bytes from string src to string dst.  The
two strings may overlap; the copy is always done in a non-destructive
manner.*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	if (dst < src)
	{
		while (i < len)
		{
			((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];
			i++;
		}
	}
	else if (dst > src)
	{
		while (len--)
			((unsigned char *) dst)[len] = ((const unsigned char *) src)[len];
	}
	return (dst);
}
