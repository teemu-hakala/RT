/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_stick_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:43:47 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 14:43:56 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

uint64_t	stick_size(uint64_t size)
{
	unsigned char	c;

	if (size == (uint64_t)(-1))
		return (0);
	c = 0;
	while (size >> c != 0)
		c++;
	if (c < 64)
		return (0x1U << c);
	return ((uint64_t)(-1));
}