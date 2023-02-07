/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shadow_occlusion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraivio <jraivio@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:29:30 by jraivio           #+#    #+#             */
/*   Updated: 2023/02/07 14:57:32 by jraivio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	set_shadow_occlusion(t_world *world, t_hit *hit)
{
	uint64_t	i;
	t_intersect	*current;

	i = 0;
	hit->computations.vectors.in_shadow = true;
	while (i < world->intersections.len)
	{
		current = (t_intersect *)vec_get(&world->intersections, i++);
		hit->computations.vectors.shadow_occlusion += \
			0.5 - current->material.transparency / 2;
	}
}
