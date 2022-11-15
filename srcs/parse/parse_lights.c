/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:06:15 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 11:48:14 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_light	light_prototype(void)
{
	return ((t_light){
		.position = point(-10, 10, -10),
		.intensity = colour(1, 1, 1, 1),
		.transform = default_transform_1(),
	});
}

void	find_light_subobject_keyword(t_light *light, t_parser *parser)
{
	find_double_quote(parser);
	if (ft_strncmp(&parser->string[parser->c], "position\"", 9) == 0)
	{
		parser->c += sizeof("position\"") - 1;
		find_colon(parser);
		parse_tuple(&light->position, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "transform\"", 10) == 0)
	{
		parser->c += sizeof("transform\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		parse_transform(&light->transform, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "intensity\"", 10) == 0)
	{
		parser->c += sizeof("intensity\"") - 1;
		find_colon(parser);
		parse_tuple(&light->intensity, parser);
	}
	else
		handle_errors("syntax error light object");
}

void	parse_light(t_parser *parser, t_light *light)
{
	find_light_subobject_keyword(light, parser);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		parse_light(parser, light);
	}
	else if (!find_matching_bracket(parser))
		handle_errors("light syntax error");
}

int	find_light(t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"light\"", 7) == 0)
	{
		parser->c += sizeof("\"light\"") - 1;
		find_colon(parser);
		return (true);
	}
	return (false);
}

void	parse_lights(t_world *world, t_parser *parser)
{
	t_light	light;

	find_colon(parser);
	find_open_bracket(parser);
	find_open_bracket(parser);
	while (find_light(parser))
	{
		find_open_bracket(parser);
		light = light_prototype();
		if (find_matching_bracket(parser) && parser->string[parser->c] == ',')
			parser->c++;
		else
			parse_light(parser, &light);
		if (vec_push(&world->lights, &light) == VEC_ERROR)
			handle_errors("vec_push light error");
		transform_object(&light.transform);
		if (!find_matching_bracket(parser))
			handle_errors("brackets syntax error");
		else if (parser->string[parser->c] == ',')
		{
			parser->c++;
			find_open_bracket(parser);
		}
	}
	if (!find_matching_bracket(parser))
		handle_errors("brackets syntax error");
}
