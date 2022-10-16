/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 10:25:29 by thakala           #+#    #+#             */
/*   Updated: 2022/10/15 10:51:44 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_tuple	normal_at_plane(t_object *object, t_tuple *point_at)
{
	(void)object;
	(void)point_at;
}

t_tuple	normal_at_sphere(t_object *object, t_tuple *point_at)
{
	t_tuple	origin;

	origin = (t_tuple){.tuple.units = (t_units){0, 0, 0, POINT_1}};
	origin = tuple_sub(point_at, &origin);
	return (normalize(&origin));
}

t_tuple	normal_at_cone(t_object *object, t_tuple *point_at)
{
	(void)object;
	(void)point_at;
}

t_tuple	normal_at_cylinder(t_object *object, t_tuple *point_at)
{
	(void)object;
	(void)point_at;
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
