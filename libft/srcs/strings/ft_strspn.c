/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:27:15 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/09 11:27:25 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s, const char *charset)
{
	size_t	span;
	size_t	c;
	char	found;

	span = 0;
	--s;
	while (1)
	{
		++s;
		c = 0;
		found = 0;
		while (*s && charset[c])
		{
			if (charset[c++] == *s)
			{
				++span;
				found = 1;
				break ;
			}
		}
		if (!found || !*s)
			return (span);
	}
}