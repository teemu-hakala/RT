/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:00:07 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/12 13:50:27 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	handle_parser_errors(char *str, t_parser *parser)
{
	int64_t		start_point;
	uint64_t	remainder;
	uint64_t	end_point;
	
	start_point = parser->c - START_BUFFER;
	remainder = 0;
	if (start_point < 0)
	{
		remainder = -start_point;
		start_point = 0;
	}
	end_point = start_point;
	while (parser->string[end_point] != '\0' && remainder + end_point < parser->c + END_BUFFER)
	{
		end_point++;
	}
	ft_stderror(str);
	write(1, &parser->string[start_point], end_point - start_point);
	exit(EXIT_FAILURE);
}

void	handle_errors(char *str)
{
	ft_stderror(str);
	exit(EXIT_FAILURE);
}
