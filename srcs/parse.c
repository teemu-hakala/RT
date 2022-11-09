#include "RTv1.h"

void	parse_into(t_world *world, const int file_descriptor)
{
	while (1)
	{

	}
}

void	open_scene_into(t_win *win, const char *str)
{
	win->fd = open(str, O_RDONLY);
	if (win->fd < 0)
		handle_errors("unable to open file");
}

void	parse_light()
{
	
}