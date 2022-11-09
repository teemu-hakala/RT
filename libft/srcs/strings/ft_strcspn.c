/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:26:11 by thakala           #+#    #+#             */
/*   Updated: 2022/11/09 11:26:17 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *s, const char *charset)
{
	size_t	span;
	size_t	c;
	char	found;

	if (!*s)
		return (0);
	span = 0;
	while (1)
	{
		c = 0;
		found = 0;
		while (charset[c])
		{
			if (charset[c++] == *s)
			{
				found = 1;
				break ;
			}
		}
		span += !found;
		if (found || !*++s)
			return (span);
	}
}
