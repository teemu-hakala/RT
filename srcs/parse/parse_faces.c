/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_faces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:36:52 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/12 13:55:51 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static void	set_up_and_down(t_texture *texture, t_parser *parser)
{
	if (ft_strncmp(&parser->string[parser->c], "\"up\"", 4) == 0)
	{
		parser->c += sizeof("\"up\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_face(texture, FACE_UP);
		if (find_matching_bracket(parser))
			return ;
		set_face(texture, parser, FACE_UP);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"down\"", 6) == 0)
	{
		parser->c += sizeof("\"down\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_face(texture, FACE_DOWN);
		if (find_matching_bracket(parser))
			return ;
		set_face(texture, parser, FACE_DOWN);
	}
	else
		handle_parser_errors("incorrect face", parser);
}

static void	set_left_and_right(t_texture *texture, t_parser *parser)
{
	if (ft_strncmp(&parser->string[parser->c], "\"left\"", 6) == 0)
	{
		parser->c += sizeof("\"left\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_face(texture, FACE_LEFT);
		if (find_matching_bracket(parser))
			return ;
		set_face(texture, parser, FACE_LEFT);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"right\"", 7) == 0)
	{
		parser->c += sizeof("\"right\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_face(texture, FACE_RIGHT);
		if (find_matching_bracket(parser))
			return ;
		set_face(texture, parser, FACE_RIGHT);
	}
	else
		set_up_and_down(texture, parser);
}

static void	set_face_int(t_texture *texture, t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"front\"", 7) == 0)
	{
		parser->c += sizeof("\"front\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_face(texture, FACE_FRONT);
		if (find_matching_bracket(parser))
			return ;
		set_face(texture, parser, FACE_FRONT);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"back\"", 6) == 0)
	{
		parser->c += sizeof("\"back\"") - 1;
		find_colon(parser);
		find_open_bracket(parser);
		set_default_face(texture, FACE_BACK);
		if (find_matching_bracket(parser))
			return ;
		set_face(texture, parser, FACE_BACK);
	}
	else
		set_left_and_right(texture, parser);
}

void	parse_face(t_texture *texture, t_parser *parser)
{
	find_open_bracket(parser);
	find_open_bracket(parser);
	set_face_int(texture, parser);
	while (1)
	{
		if (find_matching_bracket(parser) == false)
			handle_parser_errors("face side syntax error", parser);
		else if (parser->string[parser->c] == ',')
		{
			parser->c++;
			find_open_bracket(parser);
			set_face_int(texture, parser);
		}
		else
			break ;
	}
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (find_matching_bracket(parser) == false)
		handle_parser_errors("face array syntax error", parser);
}
