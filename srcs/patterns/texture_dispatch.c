
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
	static const t_texture_at_fn	textures[] = {\
		no_texture_at,
		checkered_at,
		align_check_at,
		external_at};
	t_tuple	colour;

	colour = point(0, 0, 0);
	textures[texture->type](texture, map, &colour);
	return (colour);
}

t_tuple	get_appearance_colour(t_appearance *appearance, t_transform transform,
t_tuple *p)
{
	t_tuple colour;

	colour = point(0, 0, 0);
	if (appearance->pattern.type > 0)
		colour = pattern_at(&appearance->pattern, transform, p);
	else
		colour = texture_at(&appearance->texture, &appearance->texture.map);
	return (colour);
}