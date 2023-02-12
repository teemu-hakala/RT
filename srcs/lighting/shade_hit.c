/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:47:09 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/12 16:52:58 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

/* reflectance represents the fraction of light reflected*/

t_tuple	reflection_and_refraction(t_world *world, t_hit *hit)
{
	t_tuple		reflected;
	t_tuple		refracted;
	t_fl		reflectance;

	refracted = refracted_colour(world, hit);
	reflected = reflected_colour(world, hit);
	if (hit->intersection.material.reflectiveness > 0 && \
		hit->intersection.material.transparency > 0)
	{
		reflectance = schlick(hit);
		return (tuple_add(tuple_scale(reflected, reflectance), \
			tuple_scale(refracted, (1 - reflectance))));
	}
	return (tuple_add(refracted, reflected));
}

t_tuple	shade_hit(t_world *world, t_hit *hit)
{
	t_tuple		colour;
	t_light		*light;
	uint64_t	i;

	colour = point(0, 0, 0);
	i = 0;
	while (i < world->lights.len)
	{
		light = (t_light *)vec_get(&world->lights, i);
		is_shadow(world, hit, light);
		if (hit->intersection.appearance.pattern.type > 0 || \
		hit->intersection.appearance.texture.type > 0)
		{
			hit->intersection.material.init_colour = \
				get_appearance_colour(hit, &hit->computations.over_point);
		}
		colour = tuple_add(colour, \
			lighting(light, hit->computations.vectors, hit));
		i++;
	}
	return (tuple_add(colour, reflection_and_refraction(world, hit)));
}
