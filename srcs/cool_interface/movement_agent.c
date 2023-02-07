











#include "RT.h"

void	camera_upwards(t_win *win, t_fl magnitude)
{
	win->input.mouse.mode = CAMERA_UP;
	win->world.camera.transform.translation.tuple.units.y += magnitude;
	transform_camera_for_rotations(&win->world.camera);
}

void	camera_forwards(t_win *win, t_fl magnitude)
{
	win->input.mouse.mode = CAMERA_FORWARD;
	win->world.camera.transform.translation.tuple.units.z += magnitude;
	transform_camera_for_rotations(&win->world.camera);
}

void	camera_sideways(t_win *win, t_fl magnitude)
{
	win->input.mouse.mode = CAMERA_LEFT;
	win->world.camera.transform.translation.tuple.units.x += magnitude;
	transform_camera_for_rotations(&win->world.camera);
}

t_fl	step_scalar(bool left_shift)
{
	return (1 + (left_shift * SCALE_COEFFICIENT));
}

void	movement_agent(t_win *win, int key)
{
	t_keys		keys;
	t_fl		scalar;

	keys = win->input.keyboard.keys;
	scalar = step_scalar(keys.keys_bitfield.left_shift);
	if (key == KEY_Q)	
		camera_upwards(win, (scalar * UP_STEP));
	if (key == KEY_W)
		camera_forwards(win, (scalar * FORWARD_STEP));
	if (key == KEY_E)
		camera_upwards(win, (scalar * -UP_STEP));
	if (key == KEY_A)
		camera_sideways(win, (scalar * LEFT_STEP));
	if (key == KEY_S)
		camera_forwards(win, (scalar * -FORWARD_STEP));
	if (key == KEY_D)
		camera_sideways(win, (scalar * -LEFT_STEP));
	refresh_image(win);
}
