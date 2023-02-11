











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
 
int	movement_agent(void *param)
{
	t_keys		keys;
	t_fl		scalar;
	t_win		*win;

	win = (t_win *)param;
	keys = win->input.keyboard.keys;
	scalar = step_scalar(keys.keys_bitfield.left_shift);
	if (keys.keys_bitfield.q)
		camera_upwards(win, (scalar * UP_STEP));
	if (keys.keys_bitfield.w)
		camera_forwards(win, (scalar * FORWARD_STEP));
	if (keys.keys_bitfield.e)
		camera_upwards(win, (scalar * -UP_STEP));
	if (keys.keys_bitfield.a)
		camera_sideways(win, (scalar * LEFT_STEP));
	if (keys.keys_bitfield.s)
		camera_forwards(win, (scalar * -FORWARD_STEP));
	if (keys.keys_bitfield.d)
		camera_sideways(win, (scalar * -LEFT_STEP));
	refresh_image(win);
	return (0);
}
