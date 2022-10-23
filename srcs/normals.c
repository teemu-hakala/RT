/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 10:25:29 by thakala           #+#    #+#             */
/*   Updated: 2022/10/23 06:20:31 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_tuple	normal_at_plane(t_object *object, t_tuple *point_at)
{
	(void)object;
	(void)point_at;
	return (vector(1, 0, 0));
}

t_tuple	normal_at_sphere(t_object *sphere, t_tuple *point_at)
{
	t_tuple	obj_point;
	t_tuple	obj_normal;
	t_tuple	world_normal;
	t_mtx	transposed_inverse;

	obj_point = matrix_tuple_multi(&sphere->object.sphere.transform.inverse, point_at);
	obj_normal = tuple_sub(obj_point, sphere->object.sphere.origin);
	transposed_inverse = transpose_matrix(&sphere->object.sphere.transform.inverse);
	world_normal = matrix_tuple_multi(&transposed_inverse, &obj_normal);
	world_normal.tuple.units.w = 0;
	return (normalize(world_normal));
}

t_tuple	normal_at_cone(t_object *object, t_tuple *point_at)
{
	(void)object;
	(void)point_at;
	return (vector(1, 0, 0));
}

t_tuple	normal_at_cylinder(t_object *object, t_tuple *point_at)
{
	(void)object;
	(void)point_at;
	return (vector(1, 0, 0));
}

t_tuple	normal_at(t_object *object, t_tuple *point)
{
	static const t_normal_fn	normals[] = {
		normal_at_plane,
		normal_at_sphere,
		normal_at_cone,
		normal_at_cylinder};

	return (normals[object->type](object, point));
}
