/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:37:53 by thakala          #+#    #+#             */
/*   Updated: 2022/11/15 14:38:12 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_insert(t_vec *dst, void *src, uint64_t index)
{
	if (dst->alloc_size >= dst->len + 1)
	{
		ft_memmove(&dst->memory[dst->elem_size * (index + 1)],
			&dst->memory[dst->elem_size * index],
			dst->elem_size * (dst->len - index));
		dst->len++;
		ft_memcpy(&dst->memory[dst->elem_size * index], src, dst->elem_size);
	}
	else
	{
		if (vec_resize(dst, dst->alloc_size * 2) > VEC_NON_ACTION)
			return (vec_insert(dst, src, index));
		return (VEC_ERROR);
	}
	return (VEC_SUCCESS);
}
