











#include "RT.h"

static void	find_movement_keywords(t_movement *movement, t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"velocity\"", 10) == 0)
	{
		parser->c += sizeof("\"velocity\"") - 1;
		find_colon(parser);
		parse_tuple(&movement->velocity, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"time\"", 6) == 0)
	{
		parser->c += sizeof("\"time\"") - 1;
		find_colon(parser);
		movement->time = rt_atof(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"active\"", 8) == 0)
	{
		parser->c += sizeof("\"active\"") - 1;
		find_colon(parser);
		movement->active = parse_boolean(parser);
	}
}

void	parse_movement(t_movement *movement, t_parser *parser)
{
	find_movement_keywords(movement, parser);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		parse_movement(movement, parser);
	}
	else
	{
		if (find_matching_bracket(parser))
			return ;
		else
			handle_errors("movement syntax error");
	}
}
