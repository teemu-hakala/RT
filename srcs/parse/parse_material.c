/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:47:33 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 12:17:34 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static void	material_keywords_cont(t_material *material, t_parser *parser)
{
	if (ft_strncmp(&parser->string[parser->c], "shininess\"", 10) == 0)
	{
		parser->c += sizeof("shininess\"") - 1;
		find_colon(parser);
		material->shininess = rt_atof(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "init_colour\"", 12) == 0)
	{
		parser->c += sizeof("init_colour\"") - 1;
		find_colon(parser);
		parse_tuple(&material->init_colour, parser);
	}
	else
		handle_errors("material syntax error");
}

static void	find_material_keywords(t_material *material, t_parser *parser)
{
	find_double_quote(parser);
	if (ft_strncmp(&parser->string[parser->c], "ambient\"", 8) == 0)
	{
		parser->c += sizeof("ambient\"") - 1;
		find_colon(parser);
		material->ambient = rt_atof(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "diffuse\"", 8) == 0)
	{
		parser->c += sizeof("diffuse\"") - 1;
		find_colon(parser);
		material->diffuse = rt_atof(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "specular\"", 9) == 0)
	{
		parser->c += sizeof("specular\"") - 1;
		find_colon(parser);
		material->specular = rt_atof(parser);
	}
	else
		material_keywords_cont(material, parser);
}

void	parse_material(t_material *material, t_parser *parser)
{
	find_material_keywords(material, parser);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		parse_material(material, parser);
	}
	else
	{
		if (find_matching_bracket(parser))
			return ;
		else
			handle_errors("material syntax error");
	}
}
