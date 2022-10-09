/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:19:56 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:43:03 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* The memset() function writes len bytes of value c (converted to an unsigned
char) to the string b.*/

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*s1;

	s1 = str;
	while (n > 0)
	{
		*s1 = c;
		s1++;
		n--;
	}
	return (str);
}
