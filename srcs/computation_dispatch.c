/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computation_dispatch.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:07:56 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/16 13:13:13 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	prepare_plane(t_world *world)
{
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations);
}

void	prepare_sphere(t_world *world)
{
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations);
}

void	prepare_cone(t_world *world)
{
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations);
}

void	prepare_cylinder(t_world *world)
{
	prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations);
}

void	prepare_computations(t_world *world)
{
	static const t_computation_fn	\
			precompute_shape[] = {
		prepare_plane,
		prepare_sphere,
		prepare_cone,
		prepare_cylinder
	};

	precompute_shape[world->hit.intersection.shape->type - OBJECT_INDEX_OFFSET]
		(world);
}
