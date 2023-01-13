











#include "RT.h"
#include <stdio.h>

void	field_of_view_delta(t_win *win, t_fl step)
{
	win->input.mouse.mode = CAMERA_FOV;
	win->world.camera.field_of_view += step;
	transform_camera(&win->world.camera);

}

void	field_of_view_zoomer(t_win *win, int key)
{
	if (key == KEY_R)
	{
		field_of_view_delta(win, ZOOM_STEP);
	}
	else if (key == KEY_F)
	{
		field_of_view_delta(win, -ZOOM_STEP);
	}
	refresh_image(win);
}
