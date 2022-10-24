/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 16:06:22 by deelliot          #+#    #+#             */
/*   Updated: 2022/03/08 10:46:15 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The stpcpy() and strcpy() functions copy the string src to dst (including
the terminating `\0' character.)
The stpncpy() and strncpy() functions copy at most len characters from src
into dst.	If src is less than len characters long, the remainder of
dst is filled with `\0' characters.  Otherwise, dst is not terminated.

The source and destination strings should not overlap, as the behavior is
undefined.*/

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
