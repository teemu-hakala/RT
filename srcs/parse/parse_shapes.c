/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:38:08 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/12 13:56:50 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static void	find_cube(t_object *shape, t_parser *parser)
{
	if (ft_strncmp(&parser->string[parser->c], "\"cube\"", 6) == 0)
	{
		parser->c += sizeof("\"cube\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		*shape = cube_prototype();
		if (find_matching_bracket(parser))
			return ;
		parse_cube(parser, shape);
	}
	else
		handle_parser_errors("shape syntax error", parser);
}

static void	find_cone_or_cylinder(t_object *shape, t_parser *parser)
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
		find_cube(shape, parser);
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
		find_cone_or_cylinder(shape, parser);
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
		object.shape_id = world->objects.len;
		if (vec_push(&world->objects, &object) == VEC_ERROR)
			handle_parser_errors("vec_push shape error", parser);
		if (find_matching_bracket(parser) == false)
			handle_parser_errors("shapes object syntax error", parser);
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
		handle_parser_errors("shapes array syntax error", parser);
}
