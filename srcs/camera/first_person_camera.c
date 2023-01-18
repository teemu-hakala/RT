











#include "RT.h"

void	first_person_camera(t_win *win)
{
	win->world.camera.transform.rotation.tuple.rotation = \
		(t_rotation){win->world.camera.transform.rotation.\
tuple.rotation.x_wid_lat_pitch + win->input.mouse.diff.row * \
	-win->rotation_step, \
win->world.camera.transform.rotation.tuple.rotation.y_hei_vert_yaw + \
win->input.mouse.diff.col * win->rotation_step, \
		win->world.camera.transform.rotation.tuple.rotation.z_dep_long_roll, 1};
	// transform_camera(&win->world.camera);
	transform_camera_for_rotations(&win->world.camera);
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
