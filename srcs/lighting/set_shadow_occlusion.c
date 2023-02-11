/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shadow_occlusion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraivio <jraivio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:29:30 by jraivio           #+#    #+#             */
/*   Updated: 2023/02/11 12:52:15 by jraivio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	set_shadow_occlusion(t_world *world, t_hit *hit, t_fl distance)
{
	uint64_t	i;
	t_intersect	*intersect;
	t_fl		half_transparency;

	i = 0;
	hit->computations.vectors.in_shadow = true;
	hit->computations.vectors.shadow_occlusion = 0;
	while (i < world->intersections.len)
	{
		intersect = (t_intersect *)vec_get(&world->intersections, i++);
		if (intersect->time < distance && intersect->time > 0)
		{
			half_transparency = (1 - intersect->material.transparency) / 2;
			if (half_transparency + EPSILON > 0.5)
				hit->computations.vectors.shadow_occlusion += 1;
			else
				hit->computations.vectors.shadow_occlusion += half_transparency;
		}
	}
}
