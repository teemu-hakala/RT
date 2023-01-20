











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

void	parse_appearance(t_appearance *appearance, t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"pattern\"", 9) == 0)
	{
		parser->c += sizeof("\"pattern\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		if (find_matching_bracket(parser))
			return ;
		parse_pattern(&appearance->pattern, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"texture\"", 9) == 0)
	{
		parser->c += sizeof("\"texture\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		if (find_matching_bracket(parser))
			return ;
		parse_texture(&appearance->texture, parser);
	}
		// parse_appearance_cont(appearance, parser);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
		parse_appearance(appearance, parser);
	else if (find_matching_bracket(parser))
		return ;
	else
		handle_errors("error in appearance parser");
}

int	find_subobject_keyword_continued(t_parser *parser, t_object_prototype *prototype)
{
	if (ft_strncmp(&parser->string[parser->c], "\"movement\"", 10) == 0)
	{
		parser->c += sizeof("\"movement\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		if (find_matching_bracket(parser))
			return (true);
		parse_movement(prototype->movement, parser);
	}
	else
		return (false);
	return (true);
}

int	find_subobject_keyword(t_parser *parser, t_object_prototype *prototype)/*t_transform *transform, \
	t_material *material, t_appearance *appearance*/
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"transform\"", 11) == 0)
		parse_transform_subobject(parser, prototype->transform);
	else if (ft_strncmp(&parser->string[parser->c], "\"material\"", 10) == 0)
	{
		parser->c += sizeof("\"material\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		if (find_matching_bracket(parser))
			return (true);
		parse_material(prototype->material, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"appearance\"", 12) == 0)
	{
		parser->c += sizeof("\"appearance\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		if (find_matching_bracket(parser))
			return (true);
		parse_appearance(prototype->appearance, parser);
	}
	return (find_subobject_keyword_continued(parser, prototype));
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
