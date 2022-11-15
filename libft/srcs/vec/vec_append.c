/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:39:28 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 14:39:38 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_append(t_vec *dst, t_vec *src)
{
	if (dst->alloc_size - dst->len < src->len
		&& vec_resize(dst, stick_size(dst->len + src->len)) < VEC_SUCCESS)
		return (VEC_ERROR);
	ft_memcpy(&dst->memory[dst->elem_size * dst->len],
		src->memory,
		dst->elem_size * src->len);
	dst->len += src->len;
	return ((-(dst->memory == NULL)) | 0x1);
}
