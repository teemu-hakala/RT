/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_pop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:37:16 by thakala          #+#    #+#             */
/*   Updated: 2022/11/15 14:37:25 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_pop(void *dst, t_vec *src)
{
	if (src->len >= 1ULL)
	{
		ft_memcpy(dst,
			&src->memory[--src->len * src->elem_size],
			src->elem_size);
		return (VEC_SUCCESS);
	}
	return (VEC_ERROR);
}
