











#include "RT.h"

#include <stdio.h>

void	print_tuple(t_tuple tuple, const char *name)
{
	printf("%s [%lf, %lf, %lf, %lf]\n", name, tuple.tuple.units.x, tuple.tuple.units.y, tuple.tuple.units.z, tuple.tuple.units.w);
}

void	transform_object(t_transform *object)
{
	identity_matrix_set(&object->matrix);
	translate(&object->matrix, &object->translation);
	rotate(&object->matrix, &object->rotation);
	scale(&object->matrix, &object->scale);
	object->inverse = object->matrix;
	matrix_inversion(&object->inverse, 4);
}

void	transform_camera(t_camera *camera)
{
	t_mtx	view_matrix;

	identity_matrix_set(&camera->transform.matrix);
	translate(&camera->transform.matrix, &camera->transform.translation);
	print_tuple(camera->transform.translation, "translation");
	camera->transform.translation = point(0, 0, 0);
	rotate(&camera->transform.matrix, &camera->transform.rotation);
	scale(&camera->transform.matrix, &camera->transform.scale);
	print_tuple(camera->origin, "origin before");
	camera->origin = matrix_tuple_multi(&camera->transform.matrix, \
		&camera->origin);
	print_tuple(camera->origin, "origin after");
	view_matrix = view_transform(camera->origin, camera->center_of_interest, \
		vector(0, 1, 0));
	camera->transform.inverse = view_matrix;
	matrix_inversion(&camera->transform.inverse, 4);
	camera->pixel_size = get_pixel_size(camera, camera->canvas, \
		camera->field_of_view);
}

void	transform_camera_for_field_of_view(t_camera *camera)
{
	t_mtx	view_matrix;

	identity_matrix_set(&camera->transform.matrix);
	translate(&camera->transform.matrix, &camera->transform.translation);
	rotate(&camera->transform.matrix, &camera->transform.rotation);
	scale(&camera->transform.matrix, &camera->transform.scale);
	view_matrix = view_transform(camera->origin, camera->center_of_interest, \
		vector(0, 1, 0));
	matrix_multi_square(&camera->transform.matrix, &view_matrix, 4);
	camera->transform.inverse = camera->transform.matrix;
	matrix_inversion(&camera->transform.inverse, 4);
	camera->pixel_size = get_pixel_size(camera, camera->canvas, \
		camera->field_of_view);
}

void	transform_camera_for_rotations(t_camera *camera)
{
	t_mtx		view_matrix;

	identity_matrix_set(&camera->transform.matrix);
	translate(&camera->transform.matrix, &camera->transform.translation);
	rotate(&camera->transform.matrix, &camera->transform.rotation);
	scale(&camera->transform.matrix, &camera->transform.scale);
	print_tuple(camera->transform.translation, "translation");
	print_tuple(camera->transform.rotation, "rotation");
	view_matrix = view_transform(camera->origin, camera->center_of_interest, \
		vector(0, 1, 0));
	matrix_multi_square(&camera->transform.matrix, &view_matrix, 4);
	camera->transform.inverse = camera->transform.matrix;
	matrix_inversion(&camera->transform.inverse, 4);
}
