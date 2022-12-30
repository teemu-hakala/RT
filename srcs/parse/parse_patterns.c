
#include "RT.h"

void	parse_pattern_type(t_pattern *pattern, t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"vertical_stripes\"", 18) == 0)
	{
		parser->c += sizeof("\"vertical_stripes\"") - 1;
		pattern->type = PATTERN_VERTICAL_STRIPES;
		*pattern = default_vertical_stripe_pattern();
	}
	else if (ft_strncmp(&parser->string[parser->c], \
		"\"horizontal_stripes\"", 20) == 0)
	{
		parser->c += sizeof("\"horizontal_stripes\"") - 1;
		pattern->type = PATTERN_HORIZONTAL_STRIPES;
		*pattern = default_horizontal_stripe_pattern();
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"checkered\"", 11) == 0)
	{
		parser->c += sizeof("\"checkered\"") - 1;
		pattern->type = PATTERN_CHECKERED;
		*pattern = default_checkered_pattern();
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"gradient\"", 10) == 0)
	{
		parser->c += sizeof("\"gradient\"") - 1;
		pattern->type = PATTERN_GRADIENT;
		*pattern = default_gradient_pattern();
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"circle\"", 8) == 0)
	{
		parser->c += sizeof("\"circle\"") - 1;
		pattern->type = PATTERN_CIRCLES;
		*pattern = default_ring_pattern();
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"align_check\"", 13) == 0)
	{
		parser->c += sizeof("\"align_check\"") - 1;
		pattern->type = PATTERN_ALIGN_CHECK;
		*pattern = default_align_check();
	}
	else
		handle_errors("not a pattern type");
}

static void	find_pattern_keywords(t_pattern *pattern, t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"type\"", 6) == 0)
	{
		parser->c += sizeof("\"type\"") - 1;
		find_colon(parser);
		parse_pattern_type(pattern, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"width\"", 7) == 0)
	{
		parser->c += sizeof("\"width\"") - 1;
		find_colon(parser);
		pattern->width = rt_atoi(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"height\"", 8) == 0)
	{
		parser->c += sizeof("\"height\"") - 1;
		find_colon(parser);
		pattern->height = rt_atoi(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"colour_a\"", 10) == 0)
	{
		parser->c += sizeof("\"colour_a\"") - 1;
		find_colon(parser);
		parse_tuple(&pattern->colour_a, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"colour_b\"", 10) == 0)
	{
		parser->c += sizeof("\"colour_b\"") - 1;
		find_colon(parser);
		parse_tuple(&pattern->colour_b, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"transform\"", 10) == 0)
		parse_transform_subobject(parser, &pattern->transform);
	else
		handle_errors("pattern syntax error");
}

void	parse_pattern(t_pattern *pattern, t_parser *parser)
{
	find_pattern_keywords(pattern, parser);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		parse_pattern(pattern, parser);
	}
	else
	{
		if (find_matching_bracket(parser))
		{
			transform_object(&pattern->transform);
			return ;
		}
		else
			handle_errors("pattern syntax error");
	}
}
