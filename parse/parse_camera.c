#include "RTv1.h"

t_tuple	camera_origin(void)
{
	return (point(0, 0, -5));
}

t_canvas	default_canvas(void)
{
	return ((t_canvas){.vertical = HEIGHT, .horizontal = WIDTH});
}

t_transform	camera_transform(void)
{
	t_transform	d;

	d.translation = point(0, 0, 0);
	d.rotation = point(0, 0, 0);
	d.scale = point(1, 1, 1);
	transform_object(&d);
	return (d);
}