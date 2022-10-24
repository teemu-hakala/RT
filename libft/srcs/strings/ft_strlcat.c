/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:46:25 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:48:02 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* ft_strlcpy() copies up to dstsize - 1 characters from the string src to dst,
NUL-terminating the result if dstsize is not 0.

ft_strlcat() appends string src to the end of dst.  It will append at most
dstsize - ft_strlen(dst) - 1 characters.  It will then NUL-terminate, unless
dstsize is 0 or the original dst string was longer than dstsize (in
practice this should not happen as it means that either dstsize is
incorrect or that dst is not a proper string).*/

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	i = 0;
	len_dst = 0;
	len_src = ft_strlen(src);
	while (len_dst < dstsize && dst[len_dst] != '\0')
		len_dst++;
	if (len_dst == dstsize)
		return (len_src + dstsize);
	if (dstsize > 0)
	{
		while (i < (dstsize - len_dst - 1) && src[i])
		{
			dst[len_dst + i] = src[i];
			i++;
		}
		dst[len_dst + i] = '\0';
	}
	return (len_dst + len_src);
}
