/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:04:45 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 16:15:03 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/* checks to see whether the ray intersects the end caps of the
cone and if true adds the intersection to the world intersect list */

void	intersect_cone_caps(t_object *cone, t_ray *ray, \
t_world *world)
{
	t_intersect	cap_intersect;

	cap_intersect.shape = cone;
	if (cone->object.cone.closed == false || \
		(ray->direction.tuple.units.y < EPSILON && \
			ray->direction.tuple.units.y > -EPSILON))
		return ;
	cap_intersect.time = (cone->object.cone.min - \
		ray->origin.tuple.units.y) / ray->direction.tuple.units.y;
	if (check_cap(ray, cap_intersect.time, fabs(cone->object.cone.min)))
	{
		if (vec_push(&world->intersections, &cap_intersect) == VEC_ERROR)
			handle_errors("vec_push malloc error cyl_intersection");
	}
	cap_intersect.time = (cone->object.cone.max - \
		ray->origin.tuple.units.y) / ray->direction.tuple.units.y;
	if (check_cap(ray, cap_intersect.time, fabs(cone->object.cone.max)))
	{
		if (vec_push(&world->intersections, &cap_intersect) == VEC_ERROR)
			handle_errors("vec_push malloc error cone_intersection");
	}
}
