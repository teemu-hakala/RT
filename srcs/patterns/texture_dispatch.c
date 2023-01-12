
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

t_tuple	get_appearance_colour(t_info *obj_info, t_tuple *p, t_uv_map \
	(*f)(t_tuple *))
{
	t_tuple	colour;
	t_tuple	pattern_space;

	colour = point(0, 0, 0);
	if (obj_info->appearance.pattern.type > 0)
	{
		pattern_space = transform_point(p, &obj_info->transform, \
			&obj_info->appearance.pattern.transform);
		colour = pattern_at(&obj_info->appearance.pattern, &pattern_space);
	}
	else
	{
		pattern_space = transform_point(p, &obj_info->transform, \
			&obj_info->appearance.texture.transform);
		if (f == cubic_map)
		{
			obj_info->appearance.texture.face = face_from_point(&pattern_space);
		}
		obj_info->appearance.texture.map = f(&pattern_space);
		colour = texture_at(&obj_info->appearance.texture, \
			&obj_info->appearance.texture.map);
	}
	return (colour);
}
