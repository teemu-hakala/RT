/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shadow_occlusion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraivio <jraivio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:29:30 by jraivio           #+#    #+#             */
/*   Updated: 2023/02/07 16:00:03 by jraivio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	set_shadow_occlusion(t_world *world, t_hit *hit, t_fl distance)
{
	uint64_t	i;
	t_intersect	*current;

	i = 0;
	hit->computations.vectors.in_shadow = true;
	hit->computations.vectors.shadow_occlusion = 0;
	while (i < world->intersections.len)
	{
		current = (t_intersect *)vec_get(&world->intersections, i++);
		if (current->time < distance && current->time > 0)
			hit->computations.vectors.shadow_occlusion += \
				(1 - current->material.transparency) / 2;
	}
}
