/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:58:56 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:46:35 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* the strchr() function locates the first occurrence of c (converted to a
char) in the string pointed to by s.  The terminating null character is
considered to be part of the string; therefore if c is `\0', the functions
locate the terminating `\0'.*/

char	*ft_strchr(const char *string, int c)
{
	while (*string)
	{
		if (*string == c)
		{
			return ((char *)string);
		}
		string++;
	}
	if (c == '\0')
	{
		return ((char *)string);
	}
	return (NULL);
}
