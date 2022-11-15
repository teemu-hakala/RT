/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_copy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:35:13 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 14:35:21 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_copy(t_vec *dst, t_vec *src)
{
	if (src->len > dst->alloc_size)
	{
		ft_memcpy(dst->memory, src->memory, src->elem_size * dst->alloc_size);
		dst->len = dst->alloc_size;
		return (VEC_COPY_PARTIAL);
	}
	else
	{
		ft_memcpy(dst->memory, src->memory, src->elem_size * src->len);
		dst->len = src->len;
		return (VEC_COPY_FULL);
	}
}
