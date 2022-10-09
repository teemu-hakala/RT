/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:33:54 by deelliot          #+#    #+#             */
/*   Updated: 2022/08/30 14:45:08 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Takes as a parameter the address of a memory area that needs to be freed
with free(3), then puts the pointer to NULL.*/

void	ft_memdel(void **ap)
{
	if (!ap)
		return ;
	if (*ap != NULL)
	{
		free(*ap);
		*ap = NULL;
	}
}
