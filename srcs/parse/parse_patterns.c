/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_patterns.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:37:12 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/12 13:00:27 by ikarjala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static void	pattern_type_continued(t_pattern *pattern, t_parser *parser)
{
	if (ft_strncmp(&parser->string[parser->c], "\"gradient\"", 10) == 0)
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
	else if (ft_strncmp(&parser->string[parser->c], "\"perlin\"", 8) == 0)
	{
		parser->c += sizeof("\"perlin\"") - 1;
		pattern->type = PATTERN_PERLIN_NOISE;
		*pattern = default_perlin_noise();
	}
	else
		handle_errors("not a pattern type");
}

static void	parse_pattern_type(t_pattern *pattern, t_parser *parser)
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
	else if (ft_strncmp(&parser->string[parser->c], \
		"\"simple_checkered\"", 18) == 0)
	{
		parser->c += sizeof("\"simple_checkered\"") - 1;
		pattern->type = PATTERN_SIMPLE_CHECKERED;
		*pattern = default_simple_checkered_pattern();
	}
	else
		pattern_type_continued(pattern, parser);
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
	else if (ft_strncmp(&parser->string[parser->c], "\"transform\"", 11) == 0)
	{
		parse_transform_subobject(parser, &pattern->transform);
	}
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
			return ;
		else
			handle_errors("pattern syntax error");
	}
}
