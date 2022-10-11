/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 14:20:54 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/11 17:09:58 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RTv1.h"

enum e_tuple_type
{
	W_ID_VECTOR = 0,
	W_ID_POINT = 1
};


t_tuple point(double x, double y, double z)
{
	t_tuple new_point;

	new_point.tuple.x_width = x;
	new_point.tuple.y_height = y;
	new_point.tuple.z_depth = z;
	new_point.tuple.w_id = W_ID_POINT;
	new_point.tuple = (t_coords){.x_width = x, .y_height = y, \
		.z_depth = z, .w_id = W_ID_POINT};
	return (new_point);
}
// do we want to pass as an array, or as individual data points?

// t_tuple point(double *array)
// {
// 	t_tuple temp;

// 	temp.x = array[0];
// 	temp.y = array[1];
// 	temp.z = array[2];
// 	temp.w = 1;

// 	return (temp);
// }

t_tuple vector(double x, double y, double z)
{
	t_tuple new_vector;

	new_vector.tuple.x_width = x;
	new_vector.tuple.y_height = y;
	new_vector.tuple.z_depth = z;
	new_vector.tuple.w_id = W_ID_VECTOR;
	new_vector.tuple = (t_units){.x_width = x, .y_height = y, \
		.z_depth = z, .w_id = W_ID_VECTOR};
	return (new_vector);
}

t_tuple tuple_add(t_tuple *a, t_tuple *b)
{
	return ((t_tuple)
	{
		.tuple.x_width = a->tuple.x_width + b->tuple.x_width,
		.tuple.y_height = a->tuple.y_height + b->tuple.y_height,
		.tuple.z_depth = a->tuple.z_depth + b->tuple.z_depth,
		.tuple.w_id = a->tuple.w_id + b->tuple.w_id
	});
}

t_tuple tuple_sub(t_tuple *a, t_tuple *b)
{
	t_tuple temp;

	temp.x = a.x - b.x;
	temp.y = a.y - b.y;
	temp.z = a.z - b.z;
	temp.w = a.w - b.w;

	return (temp);
}

t_tuple tuple_multi(t_tuple *a, double scalar)
{
	t_tuple temp;

	temp.x = a.x * scalar;
	temp.y = a.y * scalar;
	temp.z = a.z * scalar;
	temp.w = a.w * scalar;

	return (temp);
}

t_tuple tuple_div(t_tuple *a, double scalar)
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
