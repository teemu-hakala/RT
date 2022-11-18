/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_single_light.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:19:20 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/18 13:27:47 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static void	find_light_subobject_keyword(t_light *light, t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"position\"", 10) == 0)
	{
		parser->c += sizeof("\"position\"") - 1;
		find_colon(parser);
		parse_tuple(&light->position, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"intensity\"", 11) == 0)
	{
		parser->c += sizeof("\"intensity\"") - 1;
		find_colon(parser);
		parse_tuple(&light->intensity, parser);
	}
	else
		handle_errors("syntax error light object");
}

void	parse_single_light(t_parser *parser, t_light *light)
{
	find_light_subobject_keyword(light, parser);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		parse_single_light(parser, light);
	}
	else if (!find_matching_bracket(parser))
		handle_errors("light syntax error");
}
