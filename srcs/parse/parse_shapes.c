/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:06:52 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/30 14:09:43 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static void	find_shape_cont(t_object *shape, t_parser *parser)
{
	if (ft_strncmp(&parser->string[parser->c], "\"cone\"", 6) == 0)
	{
		parser->c += sizeof("\"cone\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		*shape = cone_prototype();
		if (find_matching_bracket(parser))
			return ;
		parse_cone(parser, shape);
		transform_object(&shape->object.cone.transform);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"cylinder\"", 10) == 0)
	{
		parser->c += sizeof("\"cylinder\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		*shape = cylinder_prototype();
		if (find_matching_bracket(parser))
			return ;
		parse_cylinder(parser, shape);
		transform_object(&shape->object.cylinder.transform);
	}
	else
		handle_errors("shape syntax error");
}

static void	find_shape(t_object *shape, t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"plane\"", 7) == 0)
	{
		parser->c += sizeof("\"plane\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		*shape = plane_prototype();
		if (find_matching_bracket(parser))
			return ;
		parse_plane(parser, shape);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"sphere\"", 8) == 0)
	{
		parser->c += sizeof("\"sphere\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		*shape = sphere_prototype();
		if (find_matching_bracket(parser))
			return ;
		parse_sphere(parser, shape);
	}
	else
		find_shape_cont(shape, parser);
}

void	parse_shapes(t_world *world, t_parser *parser)
{
	t_object	object;

	find_colon(parser);
	find_open_bracket(parser);
	find_open_bracket(parser);
	find_shape(&object, parser);
	while (1)
	{
		if (vec_push(&world->objects, &object) == VEC_ERROR)
			handle_errors("vec_push shape error");
		if (find_matching_bracket(parser) == false)
			handle_errors("shapes object syntax error");
		else if (parser->string[parser->c] == ',')
		{
			parser->c++;
			find_open_bracket(parser);
			find_shape(&object, parser);
		}
		else
			break ;
	}
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (find_matching_bracket(parser) == false)
		handle_errors("shapes array syntax error");
}
// need to fix for last comma
