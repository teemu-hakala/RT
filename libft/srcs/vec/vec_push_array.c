/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:36:41 by thakala          #+#    #+#             */
/*   Updated: 2022/11/15 14:37:07 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_push_arr(t_vec *dst, void *src, uint64_t len)
{
	uint64_t	size;

	if (dst->alloc_size - len <= dst->len)
	{
		size = stick_size(
				check_multiplication_overflow(
					check_addition_overflow(dst->alloc_size, len), 2));
		if (size != (uint64_t)(-1) && size != 0)
			if (vec_resize(dst, size) <= 0)
				return (VEC_ERROR);
	}
	ft_memcpy(&dst->memory[dst->len * dst->elem_size], src, \
		len * dst->elem_size);
	dst->len += len;
	return (VEC_SUCCESS);
}
