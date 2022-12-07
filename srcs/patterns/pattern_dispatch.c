
#include "RT.h"

t_pattern_col	set_pattern_colours(t_tuple a, t_tuple b)
{
	return ((t_pattern_col){
		.a = a,
		.b = b
	});
}

void	pattern_at(t_material *material, t_tuple *point, t_transform transform)
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
	pattern_space = matrix_tuple_multi(&material->pattern.transform.inverse, \
		&object_space);
	return (patterns[material->pattern.type](material, &pattern_space));
}
