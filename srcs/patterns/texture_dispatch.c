
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

void	texture_at(t_texture *texture, t_material *material, t_uv_map *map)
{
	static const t_texture_at_fn	textures[] = {\
		no_texture_at,
		checkered_at,
		align_check_at,
		external_at};

	return (textures[texture->type](texture, material, map));
}
