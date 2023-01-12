
#include "RT.h"

t_tuple	pattern_at(t_pattern *pattern, t_tuple *p)
{
	t_tuple							colour;
	static const t_pattern_at_fn	patterns[] = {\
		none_at,
		vertical_striped_at,
		horizontal_striped_at,
		circle_at,
		gradient_at,
		simple_checkered_at};

	colour = point(0, 0, 0);
	patterns[pattern->type](pattern, p, &colour);
	return (colour);
}
