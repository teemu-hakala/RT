#include "RT.h"

static void	parse_group_keyword(t_group *group, t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"shapes\"", 8) == 0)
	{
		parser->c += sizeof("\"shapes\"") - 1;
		parse_shapes(group, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"transform\"", 11) == 0)
		parse_transform_subobject(parser, &group->transform);
	else
		handle_errors("group keyword error");
}

static void	parse_individual_group(t_group *group, t_parser *parser)
{
	parse_group_keyword(group, parser);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		parse_individual_group(group, parser);
	}
	else if (!find_matching_bracket(parser))
		handle_errors("bracket in group error");
}

void	parse_groups(t_world *world, t_parser *parser)
{
	t_group	group;

	find_colon(parser);
	find_open_bracket(parser);
	find_open_bracket(parser);
	parse_individual_group(&group, parser);
	while (1)
	{
		if (vec_push(&world->groups, &group) == VEC_ERROR)
			handle_errors("vec_push group error");
		else if (parser->string[parser->c] == ',')
		{
			parser->c++;
			find_open_bracket(parser);
			parse_individual_group(&group, parser);
		}
		else
			break ;
	}
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (find_matching_bracket(parser) == false)
		handle_errors("groups array syntax error");
}
