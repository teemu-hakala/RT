/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations_calculations.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:19:46 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 11:19:47 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static t_tuple	hit_position(t_ray *ray, t_fl distance)
{
	return (tuple_add(ray->origin, tuple_scale(ray->direction, distance)));
}

void	prepare_object(t_world *world, t_hit *hit, t_ray ray)
{
	hit->computations.time = hit->intersection.time;
	hit->computations.point = \
		hit_position(&ray, hit->computations.time);
	hit->computations.vectors.eye = tuple_scale(ray.direction, -1);
	hit->computations.vectors.surface_normal = \
		normal_at(hit->intersection.shape, &hit->computations.point);
	if (dot_product(hit->computations.vectors.surface_normal, \
		hit->computations.vectors.eye) < 0)
	{
		hit->computations.inside = true;
		hit->computations.vectors.surface_normal = \
			tuple_scale(hit->computations.vectors.surface_normal, -1);
	}
	else
		hit->computations.inside = false;
	hit->computations.over_point = \
		tuple_add(hit->computations.point, \
		tuple_scale(hit->computations.vectors.surface_normal, EPSILON));
	hit->computations.under_point = \
		tuple_sub(hit->computations.point, \
		tuple_scale(hit->computations.vectors.surface_normal, EPSILON));
	hit->computations.reflectv = reflect(ray.direction, \
		hit->computations.vectors.surface_normal);
	hit->computations.n1 = 1;
	hit->computations.n2 = 1;
	if (world->intersections.len >= 1)
		compute_refraction_index(world, hit);
}
