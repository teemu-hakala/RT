/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:00:18 by thakala           #+#    #+#             */
/*   Updated: 2022/11/11 10:26:43 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

double	rt_atof(t_parser *parser)
{
	uint64_t	d;
	char		sign;
	uint64_t	integral;
	uint64_t	fractional;
	uint64_t	decimal_digits;

	parser->atof_index = 0;
	d = 0;
	decimal_digits = 1;
	while (ft_isspace(parser->string[d]))
		d++;
	sign = 1;
	if (parser->string[d] == '+' || parser->string[d] == '-')
		sign = 44 - parser->string[d++];
	integral = 0;
	fractional = 0;
	while (ft_isdigit(parser->string[d]) && ++parser->atof_index)
		integral = 10 * integral + (parser->string[d++] - '0');
	if (parser->string[d++] == '.')
	{
		while (ft_isdigit(parser->string[d]) && ++parser->atof_index)
		{
			fractional = 10 * fractional + (parser->string[d++] - '0');
			decimal_digits *= 10;
		}
	}
	if (parser->atof_index == 0)
		handle_errors("atof error");
	parser->c += d;
	return (sign * ((double)integral + (double)fractional / decimal_digits));
}
