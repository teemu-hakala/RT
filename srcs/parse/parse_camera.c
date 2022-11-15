/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:05:21 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 10:05:23 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static t_tuple	camera_origin(void)
{
	return (point(0, 0, -5));
}

static t_canvas	default_canvas(void)
{
	return ((t_canvas){.vertical = HEIGHT, .horizontal = WIDTH});
}

void	transform_camera(t_camera *camera)
{
	t_mtx	view_matrix;

	identity_matrix_set(&camera->transform.matrix);
	translate(&camera->transform.matrix, &camera->transform.translation);
	rotate(&camera->transform.matrix, &camera->transform.rotation);
	scale(&camera->transform.matrix, &camera->transform.scale);
	view_matrix = view_transform(camera->origin, camera->center_of_interest, vector(0, 1, 0));
	matrix_multi_square(&camera->transform.matrix, &view_matrix, 4);
	camera->transform.inverse = camera->transform.matrix;
	matrix_inversion(&camera->transform.inverse, 4);
}

t_camera	camera_prototype(void)
{
	t_camera	camera;

	camera.origin = camera_origin();
	camera.transform = default_transform_1();
	camera.center_of_interest =  point(0, 0, 0);
	camera.field_of_view = M_2_PI,
	camera.size = default_canvas();
	camera.pixel_size = get_pixel_size(&camera, camera.size, camera.field_of_view);
	transform_camera(&camera);
	return (camera);
}

void	find_canvas_keywords(t_world *world, t_parser *parser)
{
	find_double_quote(parser);
	if (ft_strncmp(&parser->string[parser->c], "vertical\"", 9) == 0)
	{
		parser->c += sizeof("vertical\"") - 1;
		find_colon(parser);
		world->camera.size.vertical = rt_atoi(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "horizontal\"", 11) == 0)
	{
		parser->c += sizeof("horizontal\"") - 1;
		find_colon(parser);
		world->camera.size.horizontal = rt_atoi(parser);
	}
}

void parse_camera_subobjects(t_world *world, t_parser *parser)
{
	find_double_quote(parser);
	if (ft_strncmp(&parser->string[parser->c], "origin\"", 7) == 0)
	{
		parser->c += sizeof("origin\"") - 1;
		find_colon(parser);
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
		find_colon(parser);
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
		if (parser->string[parser->c] == ',')
		{
			parser->c++;
			find_canvas_keywords(world, parser);
		}
		if (!find_matching_bracket(parser))
			handle_errors("canvas syntax error");
	}
	else if (ft_strncmp(&parser->string[parser->c], "field_of_view\"", 14) == 0)
	{
		parser->c += sizeof("field_of_view\"") - 1;
		find_colon(parser);
		world->camera.field_of_view = rt_atof(parser);
	}
}

void	parse_camera(t_world *world, t_parser *parser)
{
	find_colon(parser);
	find_open_bracket(parser);
	if (find_matching_bracket(parser) == true)
		return ;
	parse_camera_subobjects(world, parser);
	while (parser->string[parser->c] == ',')
	{
		parser->c++;
		parse_camera_subobjects(world, parser);
	}
	if (!find_matching_bracket(parser))
		handle_errors("camera syntax error");
	transform_camera(&world->camera);
}
