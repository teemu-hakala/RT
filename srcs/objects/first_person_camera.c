











#include "RT.h"
#include <stdio.h>
void	first_person_camera(t_win *win)
{
	win->world.camera.transform.rotation.tuple.rotation = \
		(t_rotation){win->world.camera.transform.rotation.\
tuple.rotation.x_wid_lat_pitch + win->input.mouse.diff.row * -ROTATION_STEP, \
win->world.camera.transform.rotation.tuple.rotation.y_hei_vert_yaw + \
win->input.mouse.diff.col * ROTATION_STEP, \
		win->world.camera.transform.rotation.tuple.rotation.z_dep_long_roll, 1};
	transform_camera_for_rotations(&win->world.camera);
}

void	navigate_camera(t_win *win)
{
	first_person_camera(win);
	// threaded_loop_mid(win);
	if (win->progress != NULL)
	{
		pthread_mutex_lock(&win->drawn_mutex);
		if (win->drawn == false)
		{
			pthread_cancel(win->bar_thread);
			// pthread_exit(win->bar_thread);
			printf("%li : pthread_cancel\n", (long)win->bar_thread);
			pthread_mutex_unlock(&win->drawn_mutex);
		}
		else
		{
			pthread_mutex_unlock(&win->drawn_mutex);
			win->drawn = false;
			printf("win->drawn false\n");
			progress_bar_image(win, \
				&(t_canvas){.horizontal = WIDTH - 20, .vertical = 20}, BAR_CLEAR);
			pthread_create(&win->bar_thread, NULL, progress_percentage, win);
			threaded_loop(win, win->progress);
		}
	}
	//render(win, &win->world.camera);
}
