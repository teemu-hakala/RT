/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_at_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:35:07 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 11:35:09 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_tuple	normal_at_sphere(void *sphere, t_tuple *point_at)
{
	t_tuple	obj_point;
	t_tuple	obj_normal;
	t_tuple	world_normal;
	t_mtx	transposed_inverse;

	obj_point = \
		matrix_tuple_multi(&((t_sphere *)sphere)->transform.inverse, point_at);
	obj_normal = tuple_sub(obj_point, ((t_sphere *)sphere)->origin);
	transposed_inverse = \
		transpose_matrix(&((t_sphere *)sphere)->transform.inverse);
	world_normal = matrix_tuple_multi(&transposed_inverse, &obj_normal);
	world_normal.tuple.units.w = 0;
	return (normalize(world_normal));
}
