











#include "RT.h"

void	loop_filters(t_win *win)
{
	if (win->world.filter == FILTER_NONE)
		win->world.filter = SEPIA;
	else if (win->world.filter == SEPIA)
		win->world.filter = CARTOON;
	else if (win->world.filter == CARTOON)
		win->world.filter = MOTION_BLUR;
	else if (win->world.filter == MOTION_BLUR)
		win->world.filter = FILTER_NONE;
}