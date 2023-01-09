
#include "RT.h"

static void	find_face_keyword(t_texture *texture, t_parser *parser, int face)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"main\"", 6) == 0)
	{
		parser->c += sizeof("\"main\"") - 1;
		find_colon(parser);
		parse_tuple(&texture->main[face], parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"ul\"", 4) == 0)
	{
		parser->c += sizeof("\"ul\"") - 1;
		find_colon(parser);
		parse_tuple(&texture->ul[face], parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"ur\"", 4) == 0)
	{
		parser->c += sizeof("\"ur\"") - 1;
		find_colon(parser);
		parse_tuple(&texture->ur[face], parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"bl\"", 4) == 0)
	{
		parser->c += sizeof("\"bl\"") - 1;
		find_colon(parser);
		parse_tuple(&texture->bl[face], parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"br\"", 4) == 0)
	{
		parser->c += sizeof("\"br\"") - 1;
		find_colon(parser);
		parse_tuple(&texture->br[face], parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"name\"", 6) == 0)
	{
		parser->c += sizeof("\"name\"") - 1;
		find_colon(parser);
		find_name(&texture->image[face], parser);
		printf("texture name : %s\n", texture->image[face].name);
		open_ppm(&texture->image[face]);
	}
	else
		handle_errors("incorrect corner in face");

}

static void	set_face(t_texture *texture, t_parser *parser, int face)
{
	find_face_keyword(texture, parser, face);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		set_face(texture, parser, face);
	}
	else if (!find_matching_bracket(parser))
		handle_errors("face syntax error");
}

static void	set_default_face(t_texture *texture, int face)
{
	texture->main[face] = point(1, 1, 1);
	texture->ul[face] = point(1, 1, 1);
	texture->ur[face] = point(1, 1, 1);
	texture->bl[face] = point(1, 1, 1);
	texture->br[face] = point(1, 1, 1);
}

static void	set_up_and_down(t_texture *texture, t_parser *parser)
{
	if (ft_strncmp(&parser->string[parser->c], "\"up\"", 4) == 0)
	{
		parser->c += sizeof("\"up\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_face(texture, FACE_UP);
		if (find_matching_bracket(parser))
			return ;
		set_face(texture, parser, FACE_UP);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"down\"", 6) == 0)
	{
		parser->c += sizeof("\"down\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_face(texture, FACE_DOWN);
		if (find_matching_bracket(parser))
			return ;
		set_face(texture, parser, FACE_DOWN);
	}
	else
		handle_errors("incorrect face");
}

static void	set_left_and_right(t_texture *texture, t_parser *parser)
{
	if (ft_strncmp(&parser->string[parser->c], "\"left\"", 6) == 0)
	{
		parser->c += sizeof("\"left\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_face(texture, FACE_LEFT);
		if (find_matching_bracket(parser))
			return ;
		set_face(texture, parser, FACE_LEFT);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"right\"", 7) == 0)
	{
		parser->c += sizeof("\"right\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_face(texture, FACE_RIGHT);
		if (find_matching_bracket(parser))
			return ;
		set_face(texture, parser, FACE_RIGHT);
	}
	else
		set_up_and_down(texture, parser);
}

static void	set_face_int(t_texture *texture, t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"front\"", 7) == 0)
	{
		parser->c += sizeof("\"front\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_face(texture, FACE_FRONT);
		if (find_matching_bracket(parser))
			return ;
		set_face(texture, parser, FACE_FRONT);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"back\"", 6) == 0)
	{
		parser->c += sizeof("\"back\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_face(texture, FACE_BACK);
		if (find_matching_bracket(parser))
			return ;
		set_face(texture, parser, FACE_BACK);
	}
	else
		set_left_and_right(texture, parser);
}

void	parse_face(t_texture *texture, t_parser *parser)
{
	find_open_bracket(parser);
	find_open_bracket(parser);
	set_face_int(texture, parser);
	while (1)
	{
		if (find_matching_bracket(parser) == false)
			handle_errors("face side syntax error");
		else if (parser->string[parser->c] == ',')
		{
			parser->c++;
			find_open_bracket(parser);
			set_face_int(texture, parser);
		}
		else
			break ;
	}
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (find_matching_bracket(parser) == false)
		handle_errors("face array syntax error");
}
