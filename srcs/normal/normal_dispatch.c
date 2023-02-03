/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_dispatch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:35:14 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 11:35:15 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_tuple	object_to_world_space(t_mtx *inverse, t_tuple obj_space)
{
	t_mtx	transposed_inverse;
	t_tuple	world_space;

	transposed_inverse = transpose_matrix(inverse);
	world_space = matrix_tuple_multi(&transposed_inverse, &obj_space);
	world_space.tuple.units.w = 0;
	return (world_space);
}

t_tuple	normal_at(void *object, t_tuple *point)
{
	static const t_normal_fn	normals[] = {
		normal_at_plane,
		normal_at_sphere,
		normal_at_cone,
		normal_at_cylinder,
		normal_at_cube};

	return (normals[((t_object *)object)->type](object, point));
}
