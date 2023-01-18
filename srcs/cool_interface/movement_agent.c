











#include "RT.h"
#include <stdio.h>

void	camera_upwards(t_win *win, t_fl magnitude)
{
	(void)magnitude;
	win->input.mouse.mode = CAMERA_UP;
	win->world.camera.transform.translation.tuple.units.y += magnitude;
	// win->world.camera.origin.tuple.units.y += magnitude;
	win->world.camera.center_of_interest.array[Y] += magnitude;
	// transform_camera(&win->world.camera);
	transform_camera_for_rotations(&win->world.camera);
}

void	camera_forwards(t_win *win, t_fl magnitude)
{
	(void)magnitude;
	win->input.mouse.mode = CAMERA_FORWARD;
	win->world.camera.transform.translation.tuple.units.z += magnitude;
	// win->world.camera.origin.tuple.units.z += magnitude;
	win->world.camera.center_of_interest.array[Z] += magnitude;
	// transform_camera(&win->world.camera);
	transform_camera_for_rotations(&win->world.camera);
}

void	camera_sideways(t_win *win, t_fl magnitude)
{
	(void)magnitude;
	win->input.mouse.mode = CAMERA_LEFT;
	win->world.camera.transform.translation.tuple.units.x += magnitude;
	// win->world.camera.origin.tuple.units.x += magnitude;
	win->world.camera.center_of_interest.array[X] += magnitude;
	// transform_camera(&win->world.camera);
	transform_camera_for_rotations(&win->world.camera);
}

void	movement_agent(t_win *win, int key)
{
	if (key == KEY_Q)
		camera_upwards(win, UP_STEP);
	else if (key == KEY_W)
		camera_forwards(win, FORWARD_STEP);
	else if (key == KEY_E)
		camera_upwards(win, -UP_STEP);
	else if (key == KEY_A)
		camera_sideways(win, LEFT_STEP);
	else if (key == KEY_S)
		camera_forwards(win, -FORWARD_STEP);
	else if (key == KEY_D)
		camera_sideways(win, -LEFT_STEP);
	refresh_image(win);
}
