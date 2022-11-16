/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:36:18 by thakala          #+#    #+#             */
/*   Updated: 2022/11/15 14:36:29 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_push(t_vec *dst, void *src)
{
	uint64_t	size;

	if (dst->alloc_size <= dst->len)
	{
		size = check_multiplication_overflow(dst->alloc_size, 2);
		if (size == (uint64_t)(-1) || vec_resize(dst, size) <= VEC_NON_ACTION)
			return (VEC_ERROR);
	}
	ft_memcpy(&dst->memory[dst->len * dst->elem_size], src, dst->elem_size);
	dst->len++;
	return (VEC_SUCCESS);
}
