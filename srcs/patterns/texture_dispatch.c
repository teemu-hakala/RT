/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:40:11 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 12:09:47 by deelliot         ###   ########.fr       */
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
	t_tuple		colour;
	t_tuple		pattern_space;
	t_intersect	intersect;

	colour = point(0, 0, 0);
	intersect = hit->intersection;
	if (
		intersect.appearance.pattern.type > 0)
	{
		pattern_space = transform_point(p, &intersect.transform, \
			&intersect.appearance.pattern.transform);
		colour = pattern_at(&intersect.appearance.pattern, &pattern_space);
	}
	else
	{
		pattern_space = transform_point(p, &intersect.transform, \
			&intersect.appearance.texture.transform);
		if (intersect.f == cubic_map)
			intersect.appearance.texture.face = face_from_point(&pattern_space);
		intersect.appearance.texture.map = intersect.f(&pattern_space);
		colour = texture_at(&intersect.appearance.texture, \
			&intersect.appearance.texture.map);
	}
	return (colour);
}
