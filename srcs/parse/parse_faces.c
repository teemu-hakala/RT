
#include "RT.h"

static void	find_face_keyword(t_pattern *pattern, t_parser *parser, int face)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"main\"", 6) == 0)
	{
		parser->c += sizeof("\"main\"") - 1;
		find_colon(parser);
		parse_tuple(&pattern->main[face], parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"ul\"", 4) == 0)
	{
		parser->c += sizeof("\"ul\"") - 1;
		find_colon(parser);
		parse_tuple(&pattern->ul[face], parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"ur\"", 4) == 0)
	{
		parser->c += sizeof("\"ur\"") - 1;
		find_colon(parser);
		parse_tuple(&pattern->ur[face], parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"bl\"", 4) == 0)
	{
		parser->c += sizeof("\"bl\"") - 1;
		find_colon(parser);
		parse_tuple(&pattern->bl[face], parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"br\"", 4) == 0)
	{
		parser->c += sizeof("\"br\"") - 1;
		find_colon(parser);
		parse_tuple(&pattern->br[face], parser);
	}
	else
		handle_errors("incorrect corner in face");

}

static void set_colours(t_pattern *pattern, t_parser *parser, int face)
{
	find_face_keyword(pattern, parser, face);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		set_colours(pattern, parser, face);
	}
	else if (!find_matching_bracket(parser))
		handle_errors("face syntax error");
}

static void set_default_colours(t_pattern *pattern, int face)
{
	pattern->main[face] = point(1, 1, 1);
	pattern->ul[face] = point(1, 1, 1);
	pattern->ur[face] = point(1, 1, 1);
	pattern->bl[face] = point(1, 1, 1);
	pattern->br[face] = point(1, 1, 1);
}

static void set_up_and_down(t_pattern *pattern, t_parser *parser)
{
	if (ft_strncmp(&parser->string[parser->c], "\"up\"", 4) == 0)
	{
		parser->c += sizeof("\"up\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_colours(pattern, FACE_UP);
		if (find_matching_bracket(parser))
			return ;
		set_colours(pattern, parser, FACE_UP);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"down\"", 6) == 0)
	{
		parser->c += sizeof("\"down\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_colours(pattern, FACE_DOWN);
		if (find_matching_bracket(parser))
			return ;
		set_colours(pattern, parser, FACE_DOWN);
	}
	else
		handle_errors("incorrect face");
}

static void set_left_and_right(t_pattern *pattern, t_parser *parser)
{
	if (ft_strncmp(&parser->string[parser->c], "\"left\"", 6) == 0)
	{
		parser->c += sizeof("\"left\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_colours(pattern, FACE_LEFT);
		if (find_matching_bracket(parser))
			return ;
		set_colours(pattern, parser, FACE_LEFT);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"right\"", 7) == 0)
	{
		parser->c += sizeof("\"right\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_colours(pattern, FACE_RIGHT);
		if (find_matching_bracket(parser))
			return ;
		set_colours(pattern, parser, FACE_RIGHT);
	}
	else
		set_up_and_down(pattern, parser);
}

static void	set_face(t_pattern *pattern, t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"front\"", 7) == 0)
	{
		parser->c += sizeof("\"front\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_colours(pattern, FACE_FRONT);
		if (find_matching_bracket(parser))
			return ;
		set_colours(pattern, parser, FACE_FRONT);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"back\"", 6) == 0)
	{
		parser->c += sizeof("\"back\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_colours(pattern, FACE_BACK);
		if (find_matching_bracket(parser))
			return ;
		set_colours(pattern, parser, FACE_BACK);
	}
	else
		set_left_and_right(pattern, parser);
}

void	parse_face(t_pattern *pattern, t_parser *parser)
{
	find_open_bracket(parser);
	find_open_bracket(parser);
	set_face(pattern, parser);
	while (1)
	{
		if (find_matching_bracket(parser) == false)
			handle_errors("face side syntax error");
		else if (parser->string[parser->c] == ',')
		{
			parser->c++;
			find_open_bracket(parser);
			set_face(pattern, parser);
		}
		else
			break ;
	}
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (find_matching_bracket(parser) == false)
		handle_errors("face array syntax error");
}