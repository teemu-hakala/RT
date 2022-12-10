











#include "RT.h"

void	parse_transform_subobject(t_parser *parser, t_transform *transform)
{
	parser->c += sizeof("\"transform\"") - 1;
	find_colon(parser);
	find_open_bracket(parser);
	if (find_matching_bracket(parser))
		return ;
	parse_transform(transform, parser);
}

int	find_subobject_keyword(t_parser *parser, t_tuple *origin, \
	t_transform *transform, t_material *material)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"origin\"", 8) == 0)
	{
		parser->c += sizeof("\"origin\"") - 1;
		find_colon(parser);
		parse_tuple(origin, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"transform\"", 11) == 0)
		parse_transform_subobject(parser, transform);
	else if (ft_strncmp(&parser->string[parser->c], "\"material\"", 10) == 0)
	{
		parser->c += sizeof("\"material\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		if (find_matching_bracket(parser))
			return (true);
		parse_material(material, parser);
	}
	else
		return (false);
	return (true);
}

void	parse_tuple(t_tuple *tuple, t_parser *parser)
{
	int	i;

	i = 0;
	*tuple = point(0, 0, 0);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c++] == '[')
	{
		while (i < 3)
		{
			tuple->array[i] = rt_atof(parser);
			parser->c += ft_clear_whitespace(&parser->string[parser->c]);
			if (i < 2 && parser->string[parser->c++] != ',')
				handle_errors("array syntax error");
			i++;
		}
		if (parser->string[parser->c] == ']')
		{
			parser->c++;
			return ;
		}
	}
	handle_errors("DENIED: parse_tuple");
}
