
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

// void	pattern_at(t_pattern *pattern, t_material *material, \
// 	t_transform *transform, t_tuple *point)
// {
// 	t_tuple	pattern_space;

// 	pattern_space = transform_point(point, transform, &pattern->transform);

// 	static const t_pattern_at_fn	patterns[] = {\
// 		none_at,
// 		vertical_striped_at,
// 		horizontal_striped_at,
// 		circle_at,
// 		gradient_at};

// 	return (patterns[pattern->type](pattern, material, &pattern_space));
// }

void	pattern_at(t_pattern *pattern, t_material *material, \
	t_transform transform, t_tuple *point)
{
	t_tuple							object_space;
	t_tuple							pattern_space;
	static const t_pattern_at_fn	patterns[] = {\
		none_at,
		vertical_striped_at,
		horizontal_striped_at,
		circle_at,
		gradient_at};

	object_space = matrix_tuple_multi(&transform.inverse, point);
	pattern_space = matrix_tuple_multi(&pattern->transform.inverse, \
		&object_space);
	return (patterns[pattern->type](pattern, material, &pattern_space));
}
