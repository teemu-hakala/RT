/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdelarray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 13:08:37 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:45:12 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_memdelarray(void **array, size_t y)
{
	size_t	i;

	if (!array)
		return ;
	if (y == 0)
		return ;
	i = 0;
	while (i < y)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free (array);
	array = NULL;
}
