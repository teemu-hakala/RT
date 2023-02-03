/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_at_cube.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:34:44 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 11:34:46 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_tuple	normal_at_cube(void *cube, t_tuple *point_at)
{
	t_tuple	obj_pt;
	t_fl	max;

	obj_pt = matrix_tuple_multi(&((t_cube *)cube)->transform.inverse, point_at);
	max = max_double(fabs(obj_pt.tuple.units.x), fabs(obj_pt.tuple.units.y), \
		fabs(obj_pt.tuple.units.z));
	if (max == fabs(obj_pt.tuple.units.x))
		return (normalize(object_to_world_space(\
			&((t_object *)cube)->object.cube.transform.inverse, \
			vector(obj_pt.tuple.units.x, 0, 0))));
	else if (max == fabs(obj_pt.tuple.units.y))
		return (normalize(object_to_world_space(\
			&((t_object *)cube)->object.cube.transform.inverse, \
			vector(0, obj_pt.tuple.units.y, 0))));
	else
		return (normalize(object_to_world_space(\
			&((t_object *)cube)->object.cube.transform.inverse, \
			vector(0, 0, obj_pt.tuple.units.z))));
}
