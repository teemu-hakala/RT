#include "RTv1.h"

t_light	default_light(void)
{
	return ((t_light){
		.position = point(-10, 10, -10),
		.intensity = colour(1, 1, 1, 1),
		.transform = default_transform_1(),
	});
}

int	find_light_subobject_keyword(t_light *light, t_parser *parser)
{
	find_double_quote(parser);
	if (ft_strncmp(&parser->string[parser->c], "position\"", 9) == 0)
	{
		parser->c += sizeof("position\"") - 1;
		parse_tuple(&light->position, parser);
		return (1);
	}
	else if (ft_strncmp(&parser->string[parser->c], "transform\"", 10) == 0)
	{
		parser->c += sizeof("transform\"") - 1;
		parse_transform(&light->transform, parser);
		return (1);
	}
	else if (ft_strncmp(&parser->string[parser->c], "intensity\"", 10) == 0)
	{
		parser->c += sizeof("intensity\"") - 1;
		parse_tuple(&light->intensity,parser);
		return (1);
	}
	else
		return (0);
}

void	parse_light(t_parser *parser, t_light *light)
{
	find_colon(parser);
	find_open_bracket(parser);
	if (find_matching_bracket(parser))
		return ;
	else
	{
		while (find_light_subobject_keyword(&light, parser))
			parse_light(parser, light);
		if (!find_matching_bracket(parser))
			handle_errors("syntax error");
	}
}

int	find_light(t_parser *parser)
{
	find_double_quote(parser);
	if (ft_strncmp(&parser->string[parser->c], "light\"", 6) == 0)
	{
		parser->c += sizeof("light\"") - 1;
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
		light = default_light();
		parse_light(parser, &light);
		if (vec_push(&world->lights, &light) == VEC_ERROR)
			handle_errors("vec_push light error");
		if (!find_matching_bracket(parser))
			handle_errors("brackets syntax error");
	}
}
