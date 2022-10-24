/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:55:36 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:44:48 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Allocates (with malloc(3)) and returns a “fresh” memory area
The memory allocated is initialized to 0
If the allocation fails, the function returns NULL.*/

void	*ft_memalloc(size_t size)
{
	void	*temp;

	if (size != 0)
	{
		temp = (void *)malloc(sizeof(*temp) * size);
		if (temp != NULL)
		{
			ft_bzero(temp, size);
			return (temp);
		}
	}
	return (NULL);
}
