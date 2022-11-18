/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:05:21 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/18 13:21:51 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	find_canvas_keywords(t_world *world, t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"vertical\"", 10) == 0)
	{
		parser->c += sizeof("\"vertical\"") - 1;
		find_colon(parser);
		world->camera.size.vertical = rt_atoi(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"horizontal\"", 12) == 0)
	{
		parser->c += sizeof("\"horizontal\"") - 1;
		find_colon(parser);
		world->camera.size.horizontal = rt_atoi(parser);
	}
}

void	parse_canvas(t_world *world, t_parser *parser)
{
	parser->c += sizeof("\"canvas\"") - 1;
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

static void	camera_subobjects_cont(t_world *world, t_parser *parser)
{
	if (ft_strncmp(&parser->string[parser->c], \
		"\"center_of_interest\"", 20) == 0)
	{
		parser->c += sizeof("\"center_of_interest\"") - 1;
		find_colon(parser);
		parse_tuple(&world->camera.center_of_interest, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"canvas\"", 8) == 0)
	{
		parse_canvas(world, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"field_of_view\"", 15) == 0)
	{
		parser->c += sizeof("\"field_of_view\"") - 1;
		find_colon(parser);
		world->camera.field_of_view = rt_atof(parser);
	}
	else
		handle_errors("camera subobject parser error");
}

static void	parse_camera_subobjects(t_world *world, t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"origin\"", 8) == 0)
	{
		parser->c += sizeof("\"origin\"") - 1;
		find_colon(parser);
		parse_tuple(&world->camera.origin, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"transform\"", 11) == 0)
	{
		parser->c += sizeof("\"transform\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		parse_transform(&world->camera.transform, parser);
	}
	else
		camera_subobjects_cont(world, parser);
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
