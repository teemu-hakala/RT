/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:59:13 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/12 17:41:36 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_tuple	colour_at(t_world *world, t_ray ray)
{
	t_hit	hit;
	t_tuple	colour_final;

	hit.hit_check = false;
	vec_clear(&world->intersections);
	intersect_world(world, ray);
	identify_hit(world, &hit);
	if (hit.hit_check == true)
	{
		prepare_object(world, &hit, ray);
		colour_final = shade_hit(world, &hit);
		return (apply_filter(world, colour_final));
	}
	else
		return (vector(0, 0, 0));
}
