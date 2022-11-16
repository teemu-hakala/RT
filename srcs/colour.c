/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:07:49 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/16 11:34:27 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_tuple	colour_at(t_world *world)
{
	vec_clear(&world->intersections);
	intersect_world(world, world->ray);
	identify_hit(world, &world->hit);
	if (world->hit.intersection != NULL)
	{
		prepare_computations(world);
		return (shade_hit(world));
	}
	else
		return (vector(0, 0.5, 0.7));
}
