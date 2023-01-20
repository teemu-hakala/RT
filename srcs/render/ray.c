











#include "RT.h"

t_ray	ray_transform(t_ray *ray, t_mtx *transform)
{
	t_ray	result;

	result.origin = matrix_tuple_multi(transform, &ray->origin);
	result.direction = matrix_tuple_multi(transform, &ray->direction);
//	result.time = 0.0;
	return (result);
}

t_ray	ray_for_pixel(t_camera *camera, t_canvas position)
{
	t_index	offset;
	t_index	world;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;
//	double	time0;
//	double	time1;

//	time0 = 0.0;
//	time1 = 0;
	offset.row = (position.vertical + 0.5) * camera->pixel_size;
	offset.col = (position.horizontal + 0.5) * camera->pixel_size;
	world.row = camera->half_height - offset.row;
	world.col = camera->half_width - offset.col;
	pixel = point(world.col, world.row, -1);
	pixel = matrix_tuple_multi(&camera->transform.inverse, &pixel);
	origin = point(0, 0, 0);
	origin = matrix_tuple_multi(&camera->transform.inverse, &origin);
	direction = normalize(tuple_sub(pixel, origin));
	return ((t_ray){.origin = origin, .direction = direction}); // , .time = random_double(time0, time1)
}
