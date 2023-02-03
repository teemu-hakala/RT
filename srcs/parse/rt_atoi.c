/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:39:12 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 11:39:14 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

static uint64_t	ft_check_sign(const char *str, uint64_t i)
{
	if (str[i] == '-')
		return (-1);
	else
		return (1);
}

static uint64_t	ft_clear_sign(const char *str, uint64_t i)
{
	if (str[i] == '+' || str[i] == '-')
		i++;
	return (i);
}

int	rt_atoi(t_parser *parser)
{
	uint64_t	i;
	int			x;
	int			sign;

	i = ft_clear_whitespace(&parser->string[parser->c]);
	sign = ft_check_sign (&parser->string[parser->c], i);
	i = ft_clear_sign(&parser->string[parser->c], i);
	x = 0;
	while (parser->string[parser->c + i])
	{
		if (parser->string[parser-> c + i] < '0' || \
		parser->string[parser-> c + i] > '9')
			break ;
		x = (x * 10) + (parser->string[parser-> c + i] - '0');
		i++;
	}
	parser->c += i;
	return (sign * x);
}
