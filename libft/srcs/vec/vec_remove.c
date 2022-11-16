/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:38:20 by thakala          #+#    #+#             */
/*   Updated: 2022/11/15 14:38:42 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_remove(t_vec *src, uint64_t index)
{
	ft_memmove(&src->memory[src->elem_size * index],
		&src->memory[src->elem_size * (index + 1)],
		src->elem_size * (src->len - index - 1));
	src->len--;
	return (VEC_SUCCESS);
}
