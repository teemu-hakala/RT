/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:14:55 by thakala          #+#    #+#             */
/*   Updated: 2022/11/15 14:14:56 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_new(t_vec *dst, uint64_t init_len, uint64_t elem_size)
{
	uint64_t	size;

	dst->len = 0;
	dst->elem_size = elem_size;
	dst->alloc_size = init_len;
	if (dst->alloc_size > 0 && elem_size > 0)
	{
		size = check_multiplication_overflow(dst->elem_size, dst->alloc_size);
		if (size == (uint64_t)(-1))
			return (VEC_ERROR);
		dst->memory = (uint8_t *)malloc(size);
	}
	else
		dst->memory = NULL;
	return ((-(!dst->memory && ((!init_len && !elem_size) || !elem_size))) \
		| !!elem_size);
}
