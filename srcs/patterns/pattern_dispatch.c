
#include "RT.h"

void	pattern_at(t_pattern *pattern, t_material *material, t_tuple *point,
	t_transform transform)
{
	t_tuple							object_space;
	t_tuple							pattern_space;
	static const t_pattern_at_fn	patterns[] = {\
		none_at,
		striped_at,
		checkered_at,
		circle_at,
		gradient_at};

	object_space = matrix_tuple_multi(&transform.inverse, point);
	pattern_space = matrix_tuple_multi(&pattern->transform.inverse, \
		&object_space);
	return (patterns[pattern->type](pattern, material, &pattern_space));
}
