/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:00:18 by thakala           #+#    #+#             */
/*   Updated: 2022/11/09 18:18:01 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *str)
{
	char		sign;
	uint64_t	integral;
	uint64_t	fractional;
	uint64_t	decimal_digits;

	decimal_digits = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		sign = 44 - *str++;
	integral = 0;
	fractional = 0;
	while (ft_isdigit(*str))
		integral = 10 * integral + (*str++ - '0');
	if (*str++ == '.')
	{
		while (ft_isdigit(*str))
		{
			fractional = 10 * fractional + (*str++ - '0');
			decimal_digits *= 10;
		}
	}
	return (sign * ((double)integral + (double)fractional / decimal_digits));
}
