/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:38:49 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/12 13:58:45 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	find_open_bracket(t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] == '{' || parser->string[parser->c] == '[')
	{
		if (vec_push_arr(&parser->brackets, &parser->string[parser->c++], 1) \
			== VEC_ERROR)
			handle_parser_errors("vec_push_arr error", parser);
	}
	else
		handle_parser_errors("open bracket format error", parser);
}

int	find_matching_bracket(t_parser *parser)
{
	char	open_bracket;
	char	close_bracket;

	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	open_bracket = ((char *)parser->brackets.memory)[parser->brackets.len - 1];
	close_bracket = open_bracket + (open_bracket & 0x1U) + 1;
	if (parser->string[parser->c] != close_bracket)
		return (false);
	parser->brackets.len--;
	parser->c++;
	return (true);
}

void	find_colon(t_parser *parser)
{
	parser->c += ft_clear_whitespace(&parser->string[parser->c]);
	if (parser->string[parser->c] != ':')
		handle_parser_errors("colon format error", parser);
	parser->c++;
}
