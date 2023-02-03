/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:38:55 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 11:38:56 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static void	read_file_contents(t_vec *string, const int file_descriptor)
{
	char	*line;
	int		read_bytes;
	int		gnl_status;
	char	first;

	first = true;
	while (1)
	{
		gnl_status = gnl_read_ret(file_descriptor, &line, &read_bytes);
		if (gnl_status == 0)
			break ;
		if (gnl_status < 0)
			handle_errors("DENIED: get_next_line error");
		if (first)
		{
			if (vec_new(string, read_bytes * 4, sizeof(char)) == VEC_ERROR)
				handle_errors("vec_new error");
			first = false;
		}
		if (vec_push_arr(string, line, ft_strlen(line)) == VEC_ERROR)
			handle_errors("vec_push_arr error");
		free (line);
	}
	if (vec_push_arr(string, "\0", 1) == VEC_ERROR)
		handle_errors("vec_push_arr error");
}

static void	find_object_keyword(t_world *world, t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"camera\"", 8) == 0)
	{
		parser->c += sizeof("\"camera\"") - 1;
		parse_camera(world, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"lights\"", 8) == 0)
	{
		parser->c += sizeof("\"lights\"") - 1;
		parse_lights(world, parser);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"shapes\"", 8) == 0)
	{
		parser->c += sizeof("\"shapes\"") - 1;
		parse_shapes(world, parser);
	}
	else
		handle_errors("DENIED:object not recognised");
}

void	check_light(t_world *world)
{
	t_light		light;

	if (world->lights.len == 0)
	{
		light = light_prototype();
		if (vec_push(&world->lights, &light) == VEC_ERROR)
			handle_errors("light vec_push error");
	}
}

void	parse_into(t_world *world, const int file_descriptor)
{
	t_parser	parser;
	t_vec		string_vec;

	read_file_contents(&string_vec, file_descriptor);
	parser.string = (char *)string_vec.memory;
	if (vec_new(&parser.brackets, 256, sizeof(char)) == VEC_ERROR)
		handle_errors("vec_new error");
	parser.c = 0;
	find_open_bracket(&parser);
	find_object_keyword(world, &parser);
	while (1)
	{
		if (parser.string[parser.c] == ',')
		{
			parser.c++;
			find_object_keyword(world, &parser);
		}
		else if (parser.brackets.len == 0 \
			|| find_matching_bracket(&parser) == true)
			break ;
		else
			handle_errors("object syntax error");
	}
	check_light(world);
	vec_free(&string_vec);
	vec_free(&parser.brackets);
}
