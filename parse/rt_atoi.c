/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:16:53 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/11 11:21:20 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The atoi() function converts the initial portion of the string pointed to
by str to int representation.*/

#include "RTv1.h"

static int	ft_check_sign(const char *str, int i)
{
	if (str[i] == '-')
		return (-1);
	else
		return (1);
}

static int	ft_clear_sign(const char *str, int i)
{
	if (str[i] == '+' || str[i] == '-')
		i++;
	return (i);
}

int	rt_atoi(t_parser *parser)
{
	int	i;
	int	x;
	int	sign;

	i = ft_clear_whitespace(parser->string);
	sign = ft_check_sign (parser->string, i);
	i = ft_clear_sign(parser->string, i);
	x = 0;
	while (parser->string[i])
	{
		if (parser->string[i] < '0' || parser->string[i] > '9')
			break ;
		x = (x * 10) + (parser->string[i] - '0');
		i++;
	}
	parser->c += i;
	return (sign * x);
}
