/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:00:18 by thakala           #+#    #+#             */
/*   Updated: 2022/11/11 09:25:01 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	rt_atof(const char *str, uint64_t *c)
{
	uint64_t	d;
	char		sign;
	uint64_t	integral;
	uint64_t	fractional;
	uint64_t	decimal_digits;

	d = 0;
	decimal_digits = 1;
	while (ft_isspace(str[d]))
		d++;
	sign = 1;
	if (str[d] == '+' || str[d] == '-')
		sign = 44 - str[d++];
	integral = 0;
	fractional = 0;
	while (ft_isdigit(str[d]))
		integral = 10 * integral + (str[d++] - '0');
	if (str[d++] == '.')
	{
		while (ft_isdigit(str[d]))
		{
			fractional = 10 * fractional + (str[d++] - '0');
			decimal_digits *= 10;
		}
	}
	*c += d;
	return (sign * ((double)integral + (double)fractional / decimal_digits));
}
