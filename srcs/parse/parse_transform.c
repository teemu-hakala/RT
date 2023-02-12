/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:38:42 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/12 14:01:56 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

int	find_transform_keywords(t_transform *transform, t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (ft_strncmp(&parser->string[parser->c], "\"translation\"", 13) == 0)
	{
		parser->c += sizeof("\"translation\"") - 1;
		find_colon(parser);
		parse_tuple(&transform->translation, parser);
		return (true);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"rotation\"", 10) == 0)
	{
		parser->c += sizeof("\"rotation\"") - 1;
		find_colon(parser);
		parse_tuple(&transform->rotation, parser);
		return (true);
	}
	else if (ft_strncmp(&parser->string[parser->c], "\"scale\"", 7) == 0)
	{
		parser->c += sizeof("\"scale\"") - 1;
		find_colon(parser);
		parse_tuple(&transform->scale, parser);
		return (true);
	}
	return (false);
}

void	parse_transform(t_transform *transform, t_parser *parser)
{
	find_transform_keywords(transform, parser);
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == ',')
	{
		parser->c++;
		parse_transform(transform, parser);
	}
	else
	{
		if (find_matching_bracket(parser))
			return ;
		else
			handle_parser_errors("transform syntax error", parser);
	}
}
