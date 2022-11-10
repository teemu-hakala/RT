#include "RTv1.h"

void	open_scene_into(t_win *win, const char *str)
{
	win->fd = open(str, O_RDONLY);
	if (win->fd < 0)
		handle_errors("unable to open file");
}

void	read_file_contents(t_vec *string, const int file_descriptor)
{
	char	*line;
	int		read_bytes;
	int		gnl_status;
	char	first;

	first = true;
	while (1)
	{
		gnl_status = gnl_read_ret(file_descriptor, &line, &read_bytes);
		if (gnl_status == 0)
			break ;
		if (gnl_status < 0)
			handle_errors("DENIED: get_next_line error");
		if (first)
		{
			if (vec_new(string, read_bytes * 4, sizeof(char)) == VEC_ERROR)
				handle_errors("vec_new error");
			first = false;
		}
		if (vec_push_arr(string, line, read_bytes) == VEC_ERROR)
			handle_errors("vec_push_arr error");
	}
	if (vec_push_arr(string, "\0", 1) == VEC_ERROR)
		handle_errors("vec_push_arr error");
}

void	find_object_keyword(t_world *world, t_parser *parser)
{
	find_double_quote(parser);
	if (ft_strncmp(&parser->string[*parser->c], "camera\"", 7) == 0)
		parse_camera(world, parser);
	else if (ft_strncmp(&parser->string[*parser->c], "lights\"", 7) == 0)
		parse_lights(world, parser);
	else if (ft_strncmp(&parser->string[*parser->c], "shapes\"", 7) == 0)
		parse_shapes(world, parser);
	else
		handle_errors("DENIED:object not recognised");
}

void	parse_into(t_world *world, const int file_descriptor)
{
	t_parser	parser;
	t_vec		string_vec;

	read_file_contents_into(&string_vec, file_descriptor);
	parser.string = (char *)string_vec.memory;
	vec_new(&parser.brackets, 256, sizeof(char));
	parser.c = 0;
	find_open_bracket(&parser);
	while ()
		find_object_keyword(world, &parser);
}

