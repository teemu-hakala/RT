/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:00:07 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/12 16:31:30 by ekantane         ###   ########.fr       */
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
	while (parser->string[end_point] != '\0' \
		&& remainder + end_point < parser->c + END_BUFFER)
		end_point++;
	ft_stderror(str);
	write(1, &parser->string[start_point], START_BUFFER - remainder);
	if ((START_BUFFER - remainder) - (end_point - parser->c) > 0)
		write(1, "\e[41m", 5);
	write(1, &parser->string[parser->c], end_point - parser->c);
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}

void	handle_errors(char *str)
{
	ft_stderror(str);
	exit(EXIT_FAILURE);
}
