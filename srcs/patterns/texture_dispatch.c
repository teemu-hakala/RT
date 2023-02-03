/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:40:11 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 11:51:01 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_tuple	transform_point(t_tuple *point, t_transform *shape_transform, \
	t_transform *pattern_transform)
{
	t_tuple	object_space;
	t_tuple	pattern_space;

	object_space = matrix_tuple_multi(&shape_transform->inverse, point);
	pattern_space = matrix_tuple_multi(&pattern_transform->inverse, \
		&object_space);
	return (pattern_space);
}

t_tuple	texture_at(t_texture *texture, t_uv_map *map)
{
	t_tuple							colour;

	static const t_texture_at_fn	textures[] = {\
		no_texture_at,
		checkered_at,
		align_check_at,
		external_at};

	colour = point(0, 0, 0);
	textures[texture->type](texture, map, &colour);
	return (colour);
}

t_tuple	get_appearance_colour(t_hit *hit, t_tuple *p)
{
	t_tuple	colour;
	t_tuple	pattern_space;

	colour = point(0, 0, 0);
	if (hit->intersection.appearance.pattern.type > 0)
	{
		pattern_space = transform_point(p, &hit->intersection.transform, \
			&hit->intersection.appearance.pattern.transform);
		colour = pattern_at(&hit->intersection.appearance.pattern, \
			&pattern_space);
	}
	else
	{
		pattern_space = transform_point(p, &hit->intersection.transform, \
			&hit->intersection.appearance.texture.transform);
		if (hit->intersection.f == cubic_map)
		{
			hit->intersection.appearance.texture.face = \
				face_from_point(&pattern_space);
		}
		hit->intersection.appearance.texture.map = \
			hit->intersection.f(&pattern_space);
		colour = texture_at(&hit->intersection.appearance.texture, \
			&hit->intersection.appearance.texture.map);
	}
	return (colour);
}
