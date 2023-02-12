/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:37:04 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/11 14:01:55 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static void	parse_disruption(t_material *material, t_parser *parser)
{
	parser->c += sizeof("\"disruption\"") - 1;
	find_colon(parser);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == '1')
		material->disruption = true;
	else if (parser->string[parser->c] == '0')
		material->disruption = false;
	else
		handle_errors("disruption error");
	parser->c++;
}

static void	material_keywords_final(t_material *material, t_parser *parser)
{
	if (ft_strncmp(&parser->string[parser->c], "\"transparency\"", 14) \
		== 0)
	{
		parser->c += sizeof("\"transparency\"") - 1;
		find_colon(parser);
		material->transparency = rt_atof(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], \
		"\"refractive_index\"", 18) == 0)
	{
		parser->c += sizeof("\"refractive_index\"") - 1;
		find_colon(parser);
		material->refractive_index = rt_atof(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"disruption\"", 12) == 0)
		parse_disruption(material, parser);
	else
		handle_errors("not a material keyword");
}

static void	material_keywords_cont(t_material *material, t_parser *parser)
{
	if (ft_strncmp(&parser->string[parser->c], "\"shininess\"", 11) == 0)
	{
		parser->c += sizeof("\"shininess\"") - 1;
		find_colon(parser);
		material->shininess = rt_atof(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"init_colour\"", 13) == 0)
	{
		parser->c += sizeof("\"init_colour\"") - 1;
		find_colon(parser);
		parse_tuple(&material->init_colour, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"reflectiveness\"", 16) \
		== 0)
	{
		parser->c += sizeof("\"reflectiveness\"") - 1;
		find_colon(parser);
		material->reflectiveness = rt_atof(parser);
	}
	else
		material_keywords_final(material, parser);
}

static void	find_material_keywords(t_material *material, t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"ambient\"", 9) == 0)
	{
		parser->c += sizeof("\"ambient\"") - 1;
		find_colon(parser);
		material->ambient = rt_atof(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"diffuse\"", 9) == 0)
	{
		parser->c += sizeof("\"diffuse\"") - 1;
		find_colon(parser);
		material->diffuse = rt_atof(parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"specular\"", 10) == 0)
	{
		parser->c += sizeof("\"specular\"") - 1;
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
