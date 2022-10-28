#include "RTv1.h"

t_ray	ray_for_pixel(t_camera *camera, t_canvas position)
{
	t_index	offset;
	t_index	world;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;

	offset = (t_index){.row = (position.vertical + 0.5) * camera->pixel_size, \
		.col = (position.horizontal + 0.5) * camera->pixel_size};
	world = (t_index){.row = camera->half_height - offset.row, \
		.col = camera->half_width - offset.col};
	pixel = matrix_tuple_multi(&camera->transform.inverse, &(t_tuple) \
		{.tuple.units = {.x = world.col, .y = world.row, -1, POINT_1}});
	origin = matrix_tuple_multi(&camera->transform.inverse, &(t_tuple) \
		{.tuple.units = {.x = 0, .y = 0, .z = 0, .w = POINT_1}});//make it point(1,1,1)//&camera.origin);
	direction = normalize(tuple_sub(pixel, origin));
	return ((t_ray){.origin = origin, .direction = direction});
}