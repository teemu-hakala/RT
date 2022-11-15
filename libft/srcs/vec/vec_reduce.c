/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_reduce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:42:07 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 14:42:18 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_reduce(void *acc, t_vec *src, void (*f)(void *, void *))
{
	uint64_t	c;

	c = -1;
	while (++c < src->len)
		f(acc, &src->memory[src->elem_size * c]);
	return (VEC_SUCCESS);
}
