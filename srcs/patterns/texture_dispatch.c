
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

void	pattern_at(t_pattern *pattern, t_material *material, t_uv_map *map)
{
	static const t_pattern_at_fn	patterns[] = {\
		none_at,
		checkered_at,
		align_check_at
		import_at};

	return (patterns[pattern->type](pattern, material, map));
}
