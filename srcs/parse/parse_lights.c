/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:06:15 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/16 11:25:37 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_light	light_prototype(void)
{
	return ((t_light){
		.position = point(-10, 10, -10),
		.intensity = vector(1, 1, 1),
		.transform = default_transform_1(),
	});
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

void	parse_lights_while(t_world *world, t_parser *parser)
{
	t_light	light;

	find_open_bracket(parser);
	light = light_prototype();
	if (find_matching_bracket(parser) && parser->string[parser->c] == ',')
		parser->c++;
	else
		parse_single_light(parser, &light);
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

void	parse_lights(t_world *world, t_parser *parser)
{
	find_colon(parser);
	find_open_bracket(parser);
	find_open_bracket(parser);
	while (find_light(parser))
	{
		parse_lights_while(world, parser);
	}
	if (!find_matching_bracket(parser))
		handle_errors("brackets syntax error");
}
