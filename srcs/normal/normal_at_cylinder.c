/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_at_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:34:52 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/11 18:43:27 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_tuple	normal_at_cylinder(void *cylinder, t_tuple *point_at)
{
	t_fl	distance;
	t_tuple	obj_point;
	t_tuple	obj_normal;

	obj_point = matrix_tuple_multi(&((t_cylinder *)cylinder)->transform.inverse,
			point_at);
	distance = (obj_point.tuple.units.x * obj_point.tuple.units.x) + \
		(obj_point.tuple.units.z * obj_point.tuple.units.z);
	if (distance < 1 && (obj_point.tuple.units.y >= \
		((((t_object *)cylinder)->object.cylinder.max) - EPSILON)))
		obj_normal = vector(0, 1, 0);
	else if (distance < 1 && (obj_point.tuple.units.y <= \
		((((t_object *)cylinder)->object.cylinder.min) + EPSILON)))
		obj_normal = vector(0, -1, 0);
	else
		obj_normal = vector(obj_point.tuple.units.x, 0, \
			obj_point.tuple.units.z);
	if (((t_cylinder *)cylinder)->material.disruption == true)
		obj_normal = perturb_normal(&obj_point, obj_normal);
	return (normalize(object_to_world_space(\
			&((t_object *)cylinder)->object.cylinder.transform.inverse, \
				obj_normal)));
}
