/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:06:52 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 10:06:53 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	find_shape(t_object *shape, t_parser *parser)
{
	find_double_quote(parser);
	if (ft_strncmp(&parser->string[parser->c], "plane\"", 6) == 0)
	{
		parser->c += sizeof("plane\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		*shape = plane_prototype();
		if (find_matching_bracket(parser))
			return ;
		parse_plane(parser, shape);
	}
	else if (ft_strncmp(&parser->string[parser->c], "sphere\"", 7) == 0)
	{
		parser->c += sizeof("sphere\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		*shape = sphere_prototype();
		if (find_matching_bracket(parser))
			return ;
		parse_sphere(parser, shape);
	}
	else if (ft_strncmp(&parser->string[parser->c], "cone\"", 5) == 0)
	{
		parser->c += sizeof("cone\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		*shape = cone_prototype();
		if (find_matching_bracket(parser))
			return ;
		parse_cone(parser, shape);
	}
	else if (ft_strncmp(&parser->string[parser->c], "cylinder\"", 9) == 0)
	{
		parser->c += sizeof("cylinder\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		*shape = cylinder_prototype();
		if (find_matching_bracket(parser))
			return ;
		parse_cylinder(parser, shape);
	}
	else
		handle_errors("shape syntax error");
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
		if (find_matching_bracket(parser) == false)
			handle_errors("shapes object syntax error");
		if (vec_push(&world->objects, &object) == VEC_ERROR)
			handle_errors("vec_push light error");
		if (parser->string[parser->c] == ',')
		{
			parser->c++;
			find_open_bracket(parser);
			find_shape(&object, parser);
		}
		else if (find_matching_bracket(parser) == true)
			break ;
		else
			handle_errors("shapes syntax error");
	}
	if (find_matching_bracket(parser) == false)
		handle_errors("shapes array syntax error");
}
// need to fix for last comma