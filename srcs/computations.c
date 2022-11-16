/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:17:48 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/16 13:13:23 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	prepare_object(t_world *world, t_object *object, t_comp *computations)
{
	computations->time = world->hit.intersection.time;
	computations->point = hit_position(&world->ray, computations->time);
	computations->vectors.eye = tuple_scale(world->ray.direction, -1);
	computations->vectors.surface_normal = \
		normal_at(object, &computations->point);
	if (dot_product(computations->vectors.surface_normal, \
		computations->vectors.eye) < 0)
	{
		computations->inside = true;
		computations->vectors.surface_normal = \
			tuple_scale(computations->vectors.surface_normal, -1);
	}
	else
		computations->inside = false;
	computations->over_point = tuple_add(computations->point, \
		tuple_scale(computations->vectors.surface_normal, EPSILON));
}
