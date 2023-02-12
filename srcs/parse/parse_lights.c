/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:37:00 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/12 14:04:30 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_light	light_prototype(void)
{
	return ((t_light){
		.position = point(-10, 10, -10),
		.intensity = vector(1, 1, 1),
		.direction = vector(1, 0, 0),
		.type = LIGHT_SPOT
	});
}

int	find_light(t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"spot\"", 6) == 0)
	{
		parser->c += sizeof("\"spot\"") - 1;
		find_colon(parser);
		return (LIGHT_SPOT);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"parallel\"", 10) == 0)
	{
		parser->c += sizeof("\"parallel\"") - 1;
		find_colon(parser);
		return (LIGHT_PARALLEL);
	}
	return (LIGHT_NOT_FOUND);
}

void	parse_lights_while(t_world *world, t_parser *parser, \
	t_light_type light_type)
{
	t_light	light;

	find_open_bracket(parser);
	light = light_prototype();
	light.type = light_type;
	if (find_matching_bracket(parser) && parser->string[parser->c] == ',')
		parser->c++;
	else
		parse_single_light(parser, &light);
	if (vec_push(&world->lights, &light) == VEC_ERROR)
		handle_parser_errors("vec_push light error", parser);
	if (!find_matching_bracket(parser))
		handle_parser_errors("brackets syntax error", parser);
	else if (parser->string[parser->c] == ',')
	{
		parser->c++;
		find_open_bracket(parser);
	}
}

void	parse_lights(t_world *world, t_parser *parser)
{
	t_light_type	light_type;

	find_colon(parser);
	find_open_bracket(parser);
	find_open_bracket(parser);
	light_type = find_light(parser);
	while (light_type != LIGHT_NOT_FOUND)
	{
		parse_lights_while(world, parser, light_type);
		light_type = find_light(parser);
	}
	if (!find_matching_bracket(parser))
		handle_parser_errors("brackets syntax error", parser);
}
