/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:20:54 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/12 22:13:07 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_tuple	point(t_fl x, t_fl y, t_fl z)
{
	return ((t_tuple){
		.tuple.x_width = x,
		.tuple.y_height = y,
		.tuple.z_depth = z,
		.tuple.w_id = W_ID_POINT_1
	});
}

t_tuple	vector(t_fl x, t_fl y, t_fl z)
{
	return ((t_tuple){
		.tuple.x_width = x,
		.tuple.y_height = y,
		.tuple.z_depth = z,
		.tuple.w_id = W_ID_VECTOR_0
	});
}

t_tuple	tuple_add(t_tuple *a, t_tuple *b)
{
	return ((t_tuple){
		.tuple.x_width = a->tuple.x_width + b->tuple.x_width,
		.tuple.y_height = a->tuple.y_height + b->tuple.y_height,
		.tuple.z_depth = a->tuple.z_depth + b->tuple.z_depth,
		.tuple.w_id = a->tuple.w_id + b->tuple.w_id
	});
}

t_tuple	tuple_sub(t_tuple *a, t_tuple *b)
{
	return ((t_tuple){
		.tuple.x_width = a->tuple.x_width - b->tuple.x_width,
		.tuple.y_height = a->tuple.y_height - b->tuple.y_height,
		.tuple.z_depth = a->tuple.z_depth - b->tuple.z_depth,
		.tuple.w_id = a->tuple.w_id - b->tuple.w_id
	});
}

t_tuple	tuple_multi(t_tuple *a, t_fl scalar)
{
	return ((t_tuple){
		.tuple.x_width = a->tuple.x_width * scalar,
		.tuple.y_height = a->tuple.y_height * scalar,
		.tuple.z_depth = a->tuple.z_depth * scalar,
		.tuple.w_id = a->tuple.w_id * scalar
	});
}

t_tuple	tuple_div(t_tuple *a, t_fl scalar)
{
	return ((t_tuple){
		.tuple.x_width = a->tuple.x_width / scalar,
		.tuple.y_height = a->tuple.y_height / scalar,
		.tuple.z_depth = a->tuple.z_depth / scalar,
		.tuple.w_id = a->tuple.w_id / scalar
	});
}

t_fl	magnitude(t_tuple *a)
{
	if (sizeof(t_fl) == sizeof(double))
		return (sqrt(((a->tuple.x_width * a->tuple.x_width)
					+ (a->tuple.y_height * a->tuple.y_height)
					+ (a->tuple.z_depth * a->tuple.z_depth))));
	else
		return (sqrtl(((a->tuple.x_width * a->tuple.x_width)
					+ (a->tuple.y_height * a->tuple.y_height)
					+ (a->tuple.z_depth * a->tuple.z_depth))));
}

t_tuple	normalize(t_tuple* a)
{
	double	mag;

	mag = magnitude(a);
	if (mag != 0)
		return (tuple_div(a, mag));
	return ((t_tuple){
		.tuple.x_width = 0,
		.tuple.y_height = 0,
		.tuple.z_depth = 0,
		.tuple.w_id = W_ID_VECTOR_0
	});
}

t_fl	dot_product(t_tuple *a, t_tuple *b)
{
	return ((a->tuple.x_width * b->tuple.x_width)
		+ (a->tuple.y_height * b->tuple.y_height)
		+ (a->tuple.z_depth * b->tuple.z_depth)
		+ (a->tuple.w_id * b->tuple.w_id));
}

t_tuple	cross_product(t_tuple *a, t_tuple *b)
{
	return ((t_tuple){
		.tuple.x_width = a->tuple.y_height * b->tuple.z_depth
		- a->tuple.z_depth * b->tuple.y_height,
		.tuple.y_height = a->tuple.z_depth * b->tuple.x_width
		- a->tuple.x_width * b->tuple.z_depth,
		.tuple.z_depth = a->tuple.x_width * b->tuple.y_height
		- a->tuple.y_height * b->tuple.x_width
	});
}

// .tuple.x_width = a->y * b->z - a->z * b->y,
// .tuple.y_height = a->z * b->x - a->x * b->z,
// .tuple.z_depth = a->x * b->y - a->y * b->x
