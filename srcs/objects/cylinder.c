/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:04:51 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 16:14:33 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

/*this function checks whether the intersection is within the cylinder's
radius*/

int	check_cap(t_ray *ray, t_fl time, t_fl radius)
{
	t_fl	x;
	t_fl	z;

	x = ray->origin.tuple.units.x + time * ray->direction.tuple.units.x;
	z = ray->origin.tuple.units.z + time * ray->direction.tuple.units.z;
	if ((x * x) + (z * z) <= radius)
		return (true);
	else
		return (false);
}

/* checks to see whether the ray intersects the end caps of the
cylinder and if true adds the intersection to the world intersect list */

void	intersect_cylinder_caps(t_object *cylinder, t_ray *ray, \
t_world *world)
{
	t_intersect	cap_intersect;

	cap_intersect.shape = cylinder;
	if (cylinder->object.cylinder.closed == false || \
		(ray->direction.tuple.units.y < EPSILON && \
		ray->direction.tuple.units.y > -EPSILON))
		return ;
	cap_intersect.time = (cylinder->object.cylinder.min - \
		ray->origin.tuple.units.y) / ray->direction.tuple.units.y;
	if (check_cap(ray, cap_intersect.time, cylinder->object.cylinder.radius))
	{
		if (vec_push(&world->intersections, &cap_intersect) == VEC_ERROR)
			handle_errors("vec_push malloc error cyl_intersection");
	}
	cap_intersect.time = (cylinder->object.cylinder.max - \
		ray->origin.tuple.units.y) / ray->direction.tuple.units.y;
	if (check_cap(ray, cap_intersect.time, cylinder->object.cylinder.radius))
	{
		if (vec_push(&world->intersections, &cap_intersect) == VEC_ERROR)
			handle_errors("vec_push malloc error cylinder_intersection");
	}
}
