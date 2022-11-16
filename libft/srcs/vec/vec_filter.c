/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:41:50 by thakala          #+#    #+#             */
/*   Updated: 2022/11/15 14:41:58 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_filter(t_vec *dst, t_vec *src, bool (*f)(void *))
{
	uint64_t	c;
	void		*data;

	c = -1;
	while (++c < src->len)
	{
		data = &src->memory[src->elem_size * c];
		if (f(data))
			if (vec_push(dst, data) < VEC_NON_ACTION)
				return (VEC_ERROR);
	}
	return (VEC_SUCCESS);
}
