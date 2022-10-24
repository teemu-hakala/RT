/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:37:19 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:48:02 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Allocates (with malloc(3)) and returns a “fresh” string ending with ’\0’.
Each character of the string is initialized at ’\0’.
If the allocation fails the function returns NULL.*/

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(*str) * size + 1);
	if (str != NULL)
	{
		ft_bzero(str, size + 1);
		return (str);
	}
	return (NULL);
}
