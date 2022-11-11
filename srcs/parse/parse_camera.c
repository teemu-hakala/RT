#include "RTv1.h"

t_tuple	camera_origin(void)
{
	return (point(0, 0, -5));
}

t_canvas	default_canvas(void)
{
	return ((t_canvas){.vertical = HEIGHT, .horizontal = WIDTH});
}

t_transform	camera_transform(void)
{
	t_transform	d;

	d.translation = point(0, 0, 0);
	d.rotation = point(0, 0, 0);
	d.scale = point(1, 1, 1);
	transform_object(&d);
	return (d);
}

t_camera	camera_prototype()
{
	t_camera	camera;

	return (camera);
}

void	find_canvas_keywords(t_world *world, t_parser *parser)
{
	if (ft_strncmp(&parser->string[parser->c], "vertical\"", 9) == 0)
	{
		parser->c += sizeof("vertical\"") - 1;
		parse_tuple(&world->camera.origin, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "horizontal\"", 11) == 0)
	{
		parser->c += sizeof("horizontal\"") - 1;
		parse_tuple(&world->camera.origin, parser);
	}
}

void parse_camera_subobjects(t_world *world, t_parser *parser)
{
	if (ft_strncmp(&parser->string[parser->c], "origin\"", 7) == 0)
	{
		parser->c += sizeof("origin\"") - 1;
		parse_tuple(&world->camera.origin, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "transform\"", 10) == 0)
	{
		parser->c += sizeof("transform\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		parse_transform(&world->camera.transform, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "center_of_interest\"", 19) == 0)
	{
		parser->c += sizeof("center_of_interest\"") - 1;
		parse_tuple(&world->camera.center_of_interest, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "canvas\"", 5) == 0)
	{
		parser->c += sizeof("canvas\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		if (find_matching_bracket(parser) == true)
			return ;
		find_canvas_keywords(world, parser);
		if (parser->string[++parser->c] == ',')
			find_canvas_keywords(world, parser);
		else if (!find_matching_bracket(parser))
			ft_handle_errors("light syntax error");
	}
	else if (ft_strncmp(&parser->string[parser->c], "field_of_view\"", 14) == 0)
	{
		parser->c += sizeof("field_of_view\"") - 1;
		world->camera.field_of_view = rt_atof(parser);
	}
}

void	parse_camera(t_world *world, t_parser *parser)
{
	find_colon(parser);
	find_open_bracket(parser);
	world->camera = camera_prototype();
	if (find_matching_bracket(parser) == true)
		return ;
	parse_camera_subobjects(world, parser);
	find_canvas_keywords(world, parser);
	if (parser->string[++parser->c] == ',')
		parse_camera_subobjects(world, parser);
	else if (!find_matching_bracket(parser))
		ft_handle_errors("light syntax error");
}
