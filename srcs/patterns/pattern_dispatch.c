
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
	//t_tuple							pattern_space;
	static const t_pattern_at_fn	patterns[] = {\
		none_at,
		vertical_striped_at,
		horizontal_striped_at,
		checkered_at,
		circle_at,
		gradient_at,
		align_check_at};
	// pattern_space = transform_point(point, &transform, &pattern->transform);
	return (patterns[pattern->type](pattern, material, map));
}
