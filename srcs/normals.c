/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 10:25:29 by thakala           #+#    #+#             */
/*   Updated: 2022/10/21 13:39:58 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

// t_tuple	normal_at_plane(t_object *object, t_tuple *point_at)
// {
// 	(void)object;
// 	(void)point_at;
// }

// t_tuple	normal_at_sphere(t_object *object, t_tuple *point_at)
// {
// 	t_tuple	origin;

// 	origin = (t_tuple){.tuple.units = (t_units){0, 0, 0, POINT_1}};
// 	origin = tuple_sub(point_at, &origin);
// 	return (normalize(&origin));
// }

t_tuple	normal_at_sphere(t_sphere *sphere, t_tuple *point_at)
{
	t_tuple	obj_point;
	t_tuple	obj_normal;
	t_tuple	world_normal;
	t_mtx	transposed_inverse;

	obj_point = matrix_tuple_multi(&sphere->transform.inverse, point_at);
	obj_normal = tuple_sub(&obj_point, &sphere->origin);
	transposed_inverse = transpose_matrix(&sphere->transform.inverse);
	world_normal = matrix_tuple_multi(&transposed_inverse, &obj_normal);
	world_normal.tuple.units.w = 0;
	return (normalize(&world_normal));
}

// t_tuple	normal_at_cone(t_object *object, t_tuple *point_at)
// {
// 	(void)object;
// 	(void)point_at;
// }

// t_tuple	normal_at_cylinder(t_object *object, t_tuple *point_at)
// {
// 	(void)object;
// 	(void)point_at;
// }

// t_tuple	normal_at(t_object *object, t_tuple *point)
// {
// 	static const t_normal_fn	normals[] = {
// 		normal_at_plane,
// 		normal_at_sphere,
// 		normal_at_cone,
// 		normal_at_cylinder};

// 	return (normals[object->type](object, point));
// }
