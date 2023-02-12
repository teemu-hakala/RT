/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:39:06 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/12 14:03:01 by ekantane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static double	rt_atof_digits(t_parser *parser, uint64_t *d, char sign)
{
	uint64_t	integral;
	uint64_t	fractional;
	uint64_t	decimal_digits;

	decimal_digits = 1;
	integral = 0;
	fractional = 0;
	while (ft_isdigit(parser->string[*d]) && ++parser->atof_index)
		integral = 10 * integral + (parser->string[(*d)++] - '0');
	if (parser->string[*d] == '.')
	{
		(*d)++;
		while (ft_isdigit(parser->string[*d]) && ++parser->atof_index)
		{
			fractional = 10 * fractional + (parser->string[(*d)++] - '0');
			decimal_digits *= 10;
		}
		if (decimal_digits == 0)
			handle_parser_errors("user error, number too long", parser);
	}
	return (sign * ((double)integral + (double)fractional / decimal_digits));
}

double	rt_atof(t_parser *parser)
{
	uint64_t	d;
	char		sign;
	double		result;

	parser->atof_index = 0;
	d = parser->c;
	while (ft_isspace(parser->string[d]))
		d++;
	sign = 1;
	if (parser->string[d] == '+' || parser->string[d] == '-')
		sign = 44 - parser->string[d++];
	result = rt_atof_digits(parser, &d, sign);
	if (parser->atof_index == 0)
		handle_parser_errors("atof error", parser);
	parser->c = d;
	return (result);
}
