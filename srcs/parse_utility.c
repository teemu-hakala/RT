
#include "RTv1.h"

void	find_open_bracket(t_parser *parser)
{
	parser->c += ft_clear_whitespace(parser->string);
	if (parser->string[parser->c] == '{'|| parser->string[parser->c] == '[')
	 	if (vec_push_arr(&parser->brackets, &parser->string[parser->c++], 1) == VEC_ERROR)
			handle_errors("vec_push_arr error");
	else
		handle_errors("bracket format error");
}

int	find_matching_bracket(t_parser *parser)
{
	char	open_bracket;
	char	close_bracket;

	parser->c += ft_clear_whitespace(parser->string);
	open_bracket = ((char *)parser->brackets.memory)[parser->brackets.len - 1];
	close_bracket = open_bracket + (open_bracket & 0x1U) + 1;
	if (parser->string[parser->c] != close_bracket)
		return (false);
	parser->brackets.len--;
	parser->c++;
	return (true);
}

void	find_double_quote(t_parser *parser)
{
	parser->c += ft_clear_whitespace(parser->string);
	if (parser->string[parser->c] != '"')
		handle_errors("bracket format error");
	parser->c++;
}

void	find_colon(t_parser *parser)
{
	parser->c += ft_clear_whitespace(parser->string);
	if (parser->string[parser->c] != ':')
		handle_errors("bracket format error");
	parser->c++;
}

int	find_min_and_max(t_object *object, t_parser *parser)
{
	t_fl	min;
	t_fl	max;
	int		closed;

	find_double_quote(parser);
	if (!ft_strncmp(&parser->string[parser->c], "min\"", 4))
	{
		parser->c += sizeof("min\"") - 1;
		find_colon(parser);
		min = rt_atof(&parser->string, parser->c);
		if (object->type == OBJECT_CONE)
			object->object.cone.min = min;
		else
			object->object.cylinder.min = min;
		parser->c += ft_clear_whitespace(&parser->string);
		if (parser->string[++parser->c] == ',')
			find_min_and_max(object, parser);
	}
	else if (!ft_strncmp(&parser->string[parser->c], "max\"", 4))
	{
		parser->c += sizeof("max\"") - 1;
		find_colon(parser);
		max = rt_atof(&parser->string, parser->c);
		if (object->type == OBJECT_CONE)
			object->object.cone.max = max;
		else
			object->object.cylinder.max = max;
		parser->c += ft_clear_whitespace(&parser->string);
		if (parser->string[++parser->c] == ',')
			find_min_and_max(object, parser);
	}
	else if (!ft_strncmp(&parser->string[parser->c], "closed\"", 7))
	{
		parser->c += sizeof("closed\"") - 1;
		find_colon(parser);
		parser->c += ft_clear_whitespace(&parser->string);
		if (&parser->string[parser->c] == '1')
			closed = true;
		else if (&parser->string[parser->c] == '0')
			closed = false;
		else
			handle_errors("cone/cylinder syntax error");
		if (object->type == OBJECT_CONE)
			object->object.cone.closed = closed;
		else
			object->object.cylinder.closed = closed;
	}
	else
		return (false);
	return (true);
}