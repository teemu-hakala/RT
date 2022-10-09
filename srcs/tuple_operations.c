/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:20:54 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/09 16:21:19 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RTv1.h"
#include <stdio.h>

t_tuple point(double x, double y, double z)
{
	t_tuple temp;

	temp.x = x;
	temp.y = y;
	temp.z = z;
	temp.w = 1;

	return (temp);
}

t_tuple vector(double x, double y, double z)
{
	t_tuple temp;

	temp.x = x;
	temp.y = y;
	temp.z = z;
	temp.w = 0;

	return (temp);
}

t_tuple tuple_add(t_tuple a, t_tuple b)
{
	t_tuple temp;

	temp.x = a.x + b.x;
	temp.y = a.y + b.y;
	temp.z = a.z + b.z;
	temp.w = a.w + b.w;

	return (temp);
}

t_tuple tuple_sub(t_tuple a, t_tuple b)
{
	t_tuple temp;

	temp.x = a.x - b.x;
	temp.y = a.y - b.y;
	temp.z = a.z - b.z;
	temp.w = a.w - b.w;

	return (temp);
}

t_tuple tuple_multi(t_tuple a, double scalar)
{
	t_tuple temp;

	temp.x = a.x * scalar;
	temp.y = a.y * scalar;
	temp.z = a.z * scalar;
	temp.w = a.w * scalar;

	return (temp);
}

t_tuple tuple_div(t_tuple a, double scalar)
{
	t_tuple temp;

	temp.x = a.x / scalar;
	temp.y = a.y / scalar;
	temp.z = a.z / scalar;
	temp.w = a.w / scalar;

	return (temp);
}

double magnitude(t_tuple a)
{
	double temp;
	ft_bzero(&temp, sizeof temp);

	temp = sqrt(((a.x * a.x) + (a.y * a.y) + (a.z * a.z)));
	return (temp);
}

t_tuple normalize(t_tuple a)
{
	t_tuple temp;
	ft_bzero(&temp, sizeof temp);
	double mag;

	mag = magnitude(a);
	if (mag != 0)
	{
		temp.x = a.x / mag;
		temp.y = a.y / mag;
		temp.z = a.z / mag;
	}
	return (temp);
}

double dot_product(t_tuple a, t_tuple b)
{
	double temp;
	ft_bzero(&temp, sizeof temp);

	temp = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
	return (temp);
}

t_tuple cross_product(t_tuple a, t_tuple b)
{
	t_tuple temp;
	ft_bzero(&temp, sizeof temp);

	temp.x = a.y * b.z - a.z * b.y;
	temp.y = a.z * b.x - a.x * b.z;
	temp.z = a.x * b.y - a.y * b.x;
	return (temp);
}
