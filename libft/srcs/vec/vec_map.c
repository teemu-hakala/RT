/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:41:28 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 14:41:38 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_map(t_vec *dst, t_vec *src, void (*f) (void *))
{
	uint64_t	c;

	vec_copy(dst, src);
	c = -1;
	while (++c < src->len)
		f(&dst->memory[dst->elem_size * c]);
	return (VEC_SUCCESS);
}
