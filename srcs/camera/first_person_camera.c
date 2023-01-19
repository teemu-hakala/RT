











#include "RT.h"
 #	include <stdio.h>
void	print_tuple(t_tuple tuple, const char *name);
void	rot_x(t_mtx *mtx, t_fl angle);
void	rot_y(t_mtx *mtx, t_fl angle);
void	rot_z(t_mtx *mtx, t_fl angle);

t_fl	angle_between_vectors(t_tuple a, t_tuple b)
{
	t_fl	angle;

	angle = acos(dot_product(a, b) / magnitude(a) * magnitude(b));
	printf("angle_between vectors: %lf\n", angle);
	return (angle);
}

bool	calculate_initial_angle(t_tuple *rotation, t_tuple *coi, t_tuple *snap)
{
	t_tuple		coi_proj_xz;

	coi_proj_xz = vector(coi->array[X], 0, coi->array[Z]);
	rotation->array[X] = -angle_between_vectors(*coi, coi_proj_xz);
	rotation->array[Y] = -angle_between_vectors(*snap, coi_proj_xz);
	return (false);
}

void	first_person_camera(t_win *win)
{
	static t_tuple	rotation;
	static bool		first = true;
	t_object		*object;
	t_mtx			matrix;

	if (first)
		first = calculate_initial_angle(&rotation, \
			&win->world.camera.center_of_interest, &(t_tuple){{{0, 0, 1, 1}}});
	object = ((t_object *)vec_get(&win->world.objects, 0));
	transform_object(&object->object.sphere.transform);
	print_tuple(object->object.sphere.transform.translation, \
		"object->object.sphere.transform.translation");
	matrix = identity_matrix();
	rotation.array[X] += win->input.mouse.diff.row * win->rotation_step;
	rotation.array[Y] += win->input.mouse.diff.col * win->rotation_step;
print_tuple(rotation, "static rotation");
	rot_y(&matrix, rotation.array[Y]);
	rot_x(&matrix, rotation.array[X]);
	win->world.camera.center_of_interest = \
		tuple_add(matrix_tuple_multi(&matrix, &(t_tuple){{{0, 0, 1, 1}}}), \
		win->world.camera.origin);
	object->object.sphere.transform.translation = \
		win->world.camera.center_of_interest;
	transform_camera(&win->world.camera);
}

void	refresh_image(t_win *win)
{
	pthread_mutex_lock(&win->drawn_mutex);
	if (win->drawn == false)
	{
		pthread_detach(win->bar_thread);
		pthread_cancel(win->bar_thread);
	}
	pthread_mutex_unlock(&win->drawn_mutex);
	win->drawn = false;
	progress_bar_image(win, \
		&(t_canvas){.horizontal = WIDTH - 20, .vertical = 20}, BAR_CLEAR);
	pthread_create(&win->bar_thread, NULL, progress_percentage, win);
	threaded_loop(win, win->progress);
	put_keys_image(win);
	mlx_loop_hook(win->mlx, put_image, win);
}

void	navigate_camera(t_win *win)
{
	first_person_camera(win);
	if (win->progress == NULL)
		return ;
	refresh_image(win);
}
