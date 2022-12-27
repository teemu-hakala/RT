











#include "RT.h"

void first_person_camera(t_win *win)
{
	win->world.camera.transform.rotation.tuple.rotation = \
		(t_rotation){ win->world.camera.transform.rotation.\
tuple.rotation.x_wid_lat_pitch + win->input.mouse.diff.row * -ROTATION_STEP, \
win->world.camera.transform.rotation.tuple.rotation.y_hei_vert_yaw + \
win->input.mouse.diff.col * ROTATION_STEP, \
		win->world.camera.transform.rotation.tuple.rotation.z_dep_long_roll, 1};
	transform_camera(&win->world.camera);
}

void	navigate_camera(t_win *win)
{
	first_person_camera(win);
	render(win, &win->world.camera);
}
