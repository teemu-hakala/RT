
#include "RT.h"

t_tuple	pattern_at(t_pattern *pattern, t_transform transform, t_tuple *p)
{
	t_tuple	object_space;
	t_tuple	pattern_space;
	t_tuple	colour;
	static const t_pattern_at_fn	patterns[] = {\
		none_at,
		vertical_striped_at,
		horizontal_striped_at,
		circle_at,
		gradient_at,
		simple_checkered_at};

	colour = point(0, 0, 0);
	object_space = matrix_tuple_multi(&transform.inverse, p);
	pattern_space = matrix_tuple_multi(&pattern->transform.inverse, \
		&object_space);
	patterns[pattern->type](pattern, &pattern_space, &colour);
	return (colour);
}
