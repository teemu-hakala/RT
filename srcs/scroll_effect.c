











#include "RT.h"
#include <stdio.h>

void	apply_scroll_effect(t_win *win, int8_t direction)
{
	if (win->input.mouse.mode == CAMERA_UP)
		camera_upwards(win, direction * UP_STEP);
	else if (win->input.mouse.mode == CAMERA_FORWARD)
		camera_forwards(win, direction * FORWARD_STEP);
	else if (win->input.mouse.mode == CAMERA_LEFT)
		camera_sideways(win, direction * LEFT_STEP);
	if (win->input.mouse.mode != MODE_NONE)
		refresh_image(win);
}
