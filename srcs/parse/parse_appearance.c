/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_appearance.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:50:13 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 12:53:36 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	textures(t_appearance *appearance, t_parser *parser)
{
	parser->c += sizeof("\"texture\"") - 1;
	find_colon(parser);
	find_open_bracket(parser);
	if (find_matching_bracket(parser))
		return ;
	parse_texture(&appearance->texture, parser);
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
		textures(appearance, parser);

	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
		parse_appearance(appearance, parser);
	else if (find_matching_bracket(parser))
		return ;
	else
		handle_errors("error in appearance parser");
}