/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:35:33 by thakala          #+#    #+#             */
/*   Updated: 2022/11/15 14:35:44 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

/*static*/
int	vec_resize(t_vec *src, uint64_t	target_size)
{
	t_vec	data;

	data = *src;
	if (vec_new(src, target_size, src->elem_size) > VEC_NON_ACTION)
	{
		vec_copy(src, &data);
		free(data.memory);
	}
	return (src->memory != NULL);
}
