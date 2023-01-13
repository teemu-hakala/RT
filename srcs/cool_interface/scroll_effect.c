











#include "RT.h"
#include <stdio.h>

void	compound_scroll_effect(t_win *win, int8_t direction)
{
	if (win->input.mouse.mode == win->input.mouse.compounder.mode
		&& direction == win->input.mouse.compounder.direction)
		win->input.mouse.compounder.compounds++;
	else
		win->input.mouse.compounder = \
			(t_compounder){.mode = win->input.mouse.mode, \
				.direction = direction};
}

void	apply_scroll_effect(t_win *win, int8_t direction)
{
	uint64_t	c;

	compound_scroll_effect(win, direction);
	c = win->input.mouse.compounder.compounds \
		+ !win->input.mouse.compounder.compounds;
	if (win->input.mouse.mode == CAMERA_UP)
		camera_upwards(win, direction * UP_STEP * c);
	else if (win->input.mouse.mode == CAMERA_FORWARD)
		camera_forwards(win, direction * FORWARD_STEP * c);
	else if (win->input.mouse.mode == CAMERA_LEFT)
		camera_sideways(win, direction * LEFT_STEP * c);
	else if (win->input.mouse.mode == CAMERA_FOV)
		field_of_view_delta(win, direction * ZOOM_STEP * c);
	if (win->input.mouse.mode != MODE_NONE)
		refresh_image(win);
}
