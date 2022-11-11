#include "RTv1.h"

void	find_shape(t_object *shape, t_parser *parser)
{
	find_double_quote(parser);
	if (ft_strncmp(&parser->string[parser->c], "plane\"", 9) == 0)
	{
		parse_plane(&shape->object.plane, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "sphere\"", 10) == 0)
	{
		parse_sphere(&shape->object.sphere, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "cone\"", 10) == 0)
	{
		parse_cone(&shape->object.cone, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "cylinder\"", 10) == 0)
	{
		parse_cylinder(&shape->object.cylinder, parser);
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
		if (vec_push(&world->objects, &object) == VEC_ERROR)
			handle_errors("vec_push light error");
		if (parser->string[++parser->c] == ',')
			find_shape(&object, parser);
		else if (find_matching_bracket(parser) == true)
			break ;
		else
			handle_errors("shapes syntax error");
	}
	if (find_matching_bracket(parser) == false)
		handle_errors("shapes object syntax error");
	if (find_matching_bracket(parser) == false)
		handle_errors("shapes array syntax error");
}