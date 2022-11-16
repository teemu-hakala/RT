/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:10:20 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/16 15:14:49 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_tuple	normal_at_plane(void *plane, t_tuple *point_at)
{
	t_tuple	obj_normal;
	t_tuple	world_normal;
	t_mtx	transposed_inverse;

	(void)point_at;
	obj_normal = vector(0, 1, 0);
	transposed_inverse = \
		transpose_matrix(&((t_sphere *)plane)->transform.inverse);
	world_normal = matrix_tuple_multi(&transposed_inverse, &obj_normal);
	world_normal.tuple.units.w = 0;
	return (normalize(world_normal));
}

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

t_tuple	object_to_world_space(t_mtx *inverse, t_tuple obj_space)
{
	t_mtx	transposed_inverse;
	t_tuple	world_space;

	transposed_inverse = transpose_matrix(inverse);
	world_space = matrix_tuple_multi(&transposed_inverse, &obj_space);
	return (world_space);
}

t_tuple	normal_at_cone(void *cone, t_tuple *point_at)
{
	t_fl	distance;
	t_fl	y;

	y = sqrt((point_at->tuple.units.x * point_at->tuple.units.x) + \
		(point_at->tuple.units.z * point_at->tuple.units.z));
	if (point_at->tuple.units.y > 0)
		y *= -1;
	distance = (point_at->tuple.units.x * point_at->tuple.units.x) + \
		(point_at->tuple.units.z * point_at->tuple.units.z);
	if (distance < 1 && (point_at->tuple.units.y >= \
		((((t_object *)cone)->object.cone.max) - EPSILON)))
		return (normalize(object_to_world_space(\
			&((t_object *)cone)->object.cone.transform.inverse, \
			vector(0, 1, 0))));
	else if (distance < 1 && (point_at->tuple.units.y <= \
		((((t_object *)cone)->object.cone.min) + EPSILON)))
		return ((normalize(object_to_world_space(\
			&((t_object *)cone)->object.cone.transform.inverse, \
			vector(0, -1, 0)))));
	else
		return (normalize(object_to_world_space(\
			&((t_object *)cone)->object.cone.transform.inverse, \
			vector(point_at->tuple.units.x, y, point_at->tuple.units.z))));
}

t_tuple	normal_at_cylinder(void *cylinder, t_tuple *point_at)
{
	t_fl	distance;

	distance = (point_at->tuple.units.x * point_at->tuple.units.x) + \
		(point_at->tuple.units.z * point_at->tuple.units.z);
	if (distance < 1 && (point_at->tuple.units.y >= \
		((((t_object *)cylinder)->object.cylinder.max) - EPSILON)))
		return (normalize(object_to_world_space(\
			&((t_object *)cylinder)->object.cylinder.transform.inverse, \
			vector(0, 1, 0))));
	else if (distance < 1 && (point_at->tuple.units.y <= \
		((((t_object *)cylinder)->object.cylinder.min) + EPSILON)))
		return (normalize(object_to_world_space(\
			&((t_object *)cylinder)->object.cylinder.transform.inverse, \
			vector(0, -1, 0))));
	else
		return (normalize(object_to_world_space(\
			&((t_object *)cylinder)->object.cylinder.transform.inverse, \
			vector(point_at->tuple.units.x, 0, point_at->tuple.units.z))));
}

t_tuple	normal_at(void *object, t_tuple *point)
{
	static const t_normal_fn	normals[] = {
		normal_at_plane,
		normal_at_sphere,
		normal_at_cone,
		normal_at_cylinder};

	return (normals[((t_object *)object)->type \
		- OBJECT_INDEX_OFFSET](object, point));
}
