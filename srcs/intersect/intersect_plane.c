/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:21:26 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 11:21:28 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	plane_intersection(t_ray ray, void *plane, t_world *world)
{
	t_intersect	temp;

	temp = set_intersect_info(((t_plane *)plane)->material, \
	((t_plane *)plane)->appearance, ((t_plane *)plane)->transform, planar_map);
	temp.shape = plane;
	ray = ray_transform(&ray, &((t_plane *)plane)->transform.inverse);
	if (EPSILON > ray.direction.tuple.units.y \
		&& ray.direction.tuple.units.y > -EPSILON)
		return ;
	temp.time = -ray.origin.tuple.units.y / ray.direction.tuple.units.y;
	if (vec_push(&world->intersections, &temp) == VEC_ERROR)
		handle_errors("vec_push malloc error plane_intersection");
}
