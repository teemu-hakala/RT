/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_sort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:42:48 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 15:32:50 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

static int	vec_swap_elems(uint64_t elem_size, void *a, void *b)
{
	uint8_t		*swap;

	swap = (uint8_t *)malloc(sizeof(uint8_t) * elem_size);
	if (swap == NULL)
		return (VEC_ERROR);
	ft_memcpy(swap, a, elem_size);
	ft_memcpy(a, b, elem_size);
	ft_memcpy(b, swap, elem_size);
	free(swap);
	return (VEC_SUCCESS);
}

int	vec_sort(t_vec *src, int (*f)(void *, void *))
{
	uint64_t	c;

	c = (uint64_t)(-1);
	while (++c + 1 < src->len)
	{
		if (f(&src->memory[src->elem_size * c],
				&src->memory[src->elem_size * (c + 1)]) > 0)
		{
			if (vec_swap_elems(src->elem_size,
					&src->memory[src->elem_size * c],
					&src->memory[src->elem_size * (c + 1)]) < VEC_NON_ACTION)
				return (VEC_ERROR);
			c = -1;
		}
	}
	return (VEC_SUCCESS);
}
