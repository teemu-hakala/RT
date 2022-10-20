/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:20:54 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/20 12:10:37 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_tuple	point(t_fl x, t_fl y, t_fl z)
{
	return ((t_tuple){
		.tuple.units.x = x,
		.tuple.units.y = y,
		.tuple.units.z = z,
		.tuple.units.w = POINT_1
	});
}

t_tuple	vector(t_fl x, t_fl y, t_fl z)
{
	return ((t_tuple){
		.tuple.units.x = x,
		.tuple.units.y = y,
		.tuple.units.z = z,
		.tuple.units.w = VECTOR_0
	});
}

t_tuple	tuple_add(t_tuple *a, t_tuple *b)
{
	return ((t_tuple){
		.tuple.units.x = a->tuple.units.x + b->tuple.units.x,
		.tuple.units.y = a->tuple.units.y + b->tuple.units.y,
		.tuple.units.z = a->tuple.units.z + b->tuple.units.z,
		.tuple.units.w = a->tuple.units.w + b->tuple.units.w
	});
}

t_tuple	tuple_sub(t_tuple *a, t_tuple *b)
{
	return ((t_tuple){
		.tuple.units.x = a->tuple.units.x - b->tuple.units.x,
		.tuple.units.y = a->tuple.units.y - b->tuple.units.y,
		.tuple.units.z = a->tuple.units.z - b->tuple.units.z,
		.tuple.units.w = a->tuple.units.w - b->tuple.units.w
	});
}

t_tuple	tuple_scale(t_tuple *a, t_fl scalar)
{
	return ((t_tuple){
		.tuple.units.x = a->tuple.units.x * scalar,
		.tuple.units.y = a->tuple.units.y * scalar,
		.tuple.units.z = a->tuple.units.z * scalar,
		.tuple.units.w = a->tuple.units.w * scalar //pretty sure the w shouldn't be scaled up, it should remain the same right?
	});
}

t_tuple	tuple_multi(t_tuple *a, t_tuple *b)
{
	return ((t_tuple){
		.tuple.units.x = a->tuple.units.x * b->tuple.units.x,
		.tuple.units.y = a->tuple.units.y * b->tuple.units.y,
		.tuple.units.z = a->tuple.units.z * b->tuple.units.z,
		.tuple.units.w = a->tuple.units.w * b->tuple.units.w
	});
}

t_tuple	tuple_div(t_tuple *a, t_fl scalar)
{
	return ((t_tuple){
		.tuple.units.x = a->tuple.units.x / scalar,
		.tuple.units.y = a->tuple.units.y / scalar,
		.tuple.units.z = a->tuple.units.z / scalar,
		.tuple.units.w = a->tuple.units.w / scalar
	});
}

t_fl	magnitude(t_tuple *a)
{
	// if (sizeof(t_fl) == sizeof(long double))
	// 	return (sqrtl(((a->tuple.units.x * a->tuple.units.x)
	// 				+ (a->tuple.units.y * a->tuple.units.y)
	// 				+ (a->tuple.units.z * a->tuple.units.z))));
	// else
	return (sqrt(((a->tuple.units.x * a->tuple.units.x)
				+ (a->tuple.units.y * a->tuple.units.y)
				+ (a->tuple.units.z * a->tuple.units.z))));
}

t_tuple	normalize(t_tuple *a)
{
	double	mag;

	mag = magnitude(a);
	if (mag != 0)
		return (tuple_div(a, mag));
	return ((t_tuple){
		.tuple.units.x = 0,
		.tuple.units.y = 0,
		.tuple.units.z = 0,
		.tuple.units.w = VECTOR_0
	});
}

/* the dot product calculates the cosine angle between two vectors
the smaller the dot product, the larger the angle between vectors*/

/* vector length = sqrt of the dot product of the vector itself */

t_fl	dot_product(t_tuple *a, t_tuple *b)
{
	return ((a->tuple.units.x * b->tuple.units.x)
		+ (a->tuple.units.y * b->tuple.units.y)
		+ (a->tuple.units.z * b->tuple.units.z)
		+ (a->tuple.units.w * b->tuple.units.w));
}

t_tuple	cross_product(t_tuple *a, t_tuple *b)
{
	return ((t_tuple){
		.tuple.units.x = a->tuple.units.y * b->tuple.units.z
		- a->tuple.units.z * b->tuple.units.y,
		.tuple.units.y = a->tuple.units.z * b->tuple.units.x
		- a->tuple.units.x * b->tuple.units.z,
		.tuple.units.z = a->tuple.units.x * b->tuple.units.y
		- a->tuple.units.y * b->tuple.units.x
	});
}

// .tuple.units.x = a->y * b->z - a->z * b->y,
// .tuple.units.y = a->z * b->x - a->x * b->z,
// .tuple.units.z = a->x * b->y - a->y * b->x
