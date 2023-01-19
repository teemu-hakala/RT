











#include "RT.h"
void	print_tuple(t_tuple tuple, const char *name);
void	rot_x(t_mtx *mtx, t_fl angle);
void	rot_y(t_mtx *mtx, t_fl angle);
void	rot_z(t_mtx *mtx, t_fl angle);
void	first_person_camera(t_win *win)
{
	static t_tuple	rotation;
	static bool		first = true;
	static t_tuple	center_of_interest_original;
	t_object		*object;
	t_mtx			matrix;
	t_tuple			local;

	if (first)
	{
		center_of_interest_original = \
			tuple_add(win->world.camera.origin, point(0, 0, 1));
		center_of_interest_original.array[W] = VECTOR_0;
		// center_of_interest_original = win->world.camera.center_of_interest;
		first = false;
	}

	object = ((t_object *)vec_get(&win->world.objects, 0));
	object->object.sphere.transform.translation = center_of_interest_original;
	transform_object(&object->object.sphere.transform);
	print_tuple(center_of_interest_original, "center_of_interest_original");
	local = tuple_sub(center_of_interest_original, win->world.camera.origin);
	matrix = identity_matrix();
	rotation.array[X] += win->input.mouse.diff.row * win->rotation_step;
	rotation.array[Y] += win->input.mouse.diff.col * win->rotation_step;
print_tuple(rotation, "static rotation");
	// rotate(&matrix, &rotation);
	rot_y(&matrix, rotation.array[Y]);
	rot_x(&matrix, rotation.array[X]);
	win->world.camera.center_of_interest = \
		tuple_add(matrix_tuple_multi(&matrix, &(t_tuple){{{0, 0, 1, 1}}}), \
		win->world.camera.origin);
	transform_camera(&win->world.camera);
	/*win->world.camera.transform.rotation.tuple.rotation = \
		(t_rotation){win->world.camera.transform.rotation.\
tuple.rotation.x_wid_lat_pitch + win->input.mouse.diff.row * \
	-win->rotation_step, \
win->world.camera.transform.rotation.tuple.rotation.y_hei_vert_yaw + \
win->input.mouse.diff.col * win->rotation_step, \
		win->world.camera.transform.rotation.tuple.rotation.z_dep_long_roll, 1};
	// transform_camera(&win->world.camera);
	transform_camera_for_rotations(&win->world.camera);*/
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
