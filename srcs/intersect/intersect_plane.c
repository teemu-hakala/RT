/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:41:55 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/18 15:42:31 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	plane_intersection(t_ray ray, void *plane, t_world *world)
{
	enum e_vec_status	result;

	ray = ray_transform(&ray, &((t_sphere *)plane)->transform.inverse);
	if (PLANE_EPSILON > ray.direction.tuple.units.y \
		&& ray.direction.tuple.units.y > -PLANE_EPSILON)
		return ;
	result = vec_push(&world->intersections, &(t_intersect){
			.time = -ray.origin.tuple.units.y / ray.direction.tuple.units.y,
			.shape = plane});
	if (result == VEC_ERROR)
		handle_errors("vec_push malloc error plane_intersection");
}
