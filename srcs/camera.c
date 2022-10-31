#include "RTv1.h"

static t_fl	get_pixel_size(t_camera *camera, t_canvas size, t_fl field_of_view)
{
	t_fl		half_view;
	t_fl		aspect;

	half_view = (t_fl)tan(field_of_view / 2);
	aspect = (t_fl)size.horizontal / (t_fl)size.vertical;
	if (aspect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	return (camera->half_width * 2 / size.horizontal);
}

/*original:*/
t_camera	camera(t_canvas size, t_fl field_of_view)
{
	t_camera	cam;

	cam.origin = point(0, 0, -5);
	cam.transform = default_transform();
	cam.transform.matrix = view_transform(cam.origin, point(0, 0, -1), vector(0, 1, 0));
	cam.transform.inverse = cam.transform.matrix;
	matrix_inversion(&cam.transform.inverse, 4);
	cam.center_of_interest = point(0, 0, 0);
	cam.field_of_view = field_of_view;
	cam.pixel_size = get_pixel_size(&cam, size, field_of_view);
	cam.size = (t_canvas){.vertical = size.vertical, \
		.horizontal = size.horizontal};
	return (cam);
}

/*support for matrix transformation, for now: rotation*/
/*
t_camera	camera(t_canvas size, t_fl field_of_view)
{
	t_camera	cam;
	t_tuple		to_from;
	t_tuple		to;

	cam.origin = point(0, 0, -5);
	cam.transform = default_transform();
	cam.transform.rotation = (t_tuple){.tuple.units = {0, M_PI_4, 0, POINT_1}};
	rotate(&cam.transform.matrix, &cam.transform.rotation);
	to_from = tuple_sub(cam.origin, (t_tuple){.tuple.units = {0, 0, -1, POINT_1}});
	to = matrix_tuple_multi(&cam.transform.matrix, &to_from);
	cam.transform.matrix = view_transform(cam.origin, to, vector(0, 1, 0));
	cam.transform.inverse = cam.transform.matrix;
	matrix_inversion(&cam.transform.inverse, 4);
	cam.center_of_interest = point(0, 0, 0);
	cam.field_of_view = field_of_view;
	cam.pixel_size = get_pixel_size(&cam, size, field_of_view);
	cam.size = (t_canvas){.vertical = size.vertical, \
		.horizontal = size.horizontal};
	return (cam);
}
*/
