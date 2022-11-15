/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_from.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:16:06 by thakala          #+#    #+#             */
/*   Updated: 2022/11/15 14:16:13 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_from(t_vec *dst, void *src, uint64_t len, uint64_t elem_size)
{
	uint64_t	size;

	size = check_multiplication_overflow(len, elem_size);
	if (size == (uint64_t)(-1))
		return (VEC_ERROR);
	if (vec_new(dst, len, elem_size) > VEC_NON_ACTION)
	{
		ft_memcpy(dst->memory, src, size);
		dst->len = len;
	}
	return ((-(dst->memory == NULL)) | 0x1);
}
