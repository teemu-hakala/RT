#include "RTv1.h"

void	parse_light()
{

}

void	parse_into(t_world *world, const int file_descriptor)
{
	char	*line;
	int		read_bytes;
	t_vec	string;
	char	first;

	first = true;
	while (1)
	{
		read_bytes = gnl_read_ret(file_descriptor, &line);
		if (read_bytes == 0)
			break ;
		if (read_bytes < 0)
			handle_errors("DENIED: get_next_line error");
		if (first)
		{
			vec_new(&string, read_bytes * 4, sizeof(char));
			first = false;
		}
		vec_push_arr(&string, line, read_bytes);
	}
}

void	open_scene_into(t_win *win, const char *str)
{
	win->fd = open(str, O_RDONLY);
	if (win->fd < 0)
		handle_errors("unable to open file");
}
