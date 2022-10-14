/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:03:46 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/14 19:05:07 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_tuple	translate(t_tuple *tuple, t_tuple *transform)
{
	t_mtx_4	temp;

	identity_matrix_set(&temp);
	temp.array[4 * 0 + 3] = transform->array[X];
	temp.array[4 * 1 + 3] = transform->array[Y];
	temp.array[4 * 2 + 3] = transform->array[Z];
	return (matrix_tuple_multi(&temp, tuple));
}

t_tuple	scale(t_tuple *tuple, t_tuple *transform)
{
	t_mtx_4	temp;

	identity_matrix_set(&temp);
	temp.array[4 * 0 + 0] = transform->array[X];
	temp.array[4 * 1 + 1] = transform->array[Y];
	temp.array[4 * 2 + 2] = transform->array[Z];
	return (matrix_tuple_multi(&temp, tuple));
}

t_tuple	rot_x(t_tuple *tuple, t_fl angle)
{
	t_mtx_4	temp;

	identity_matrix_set(&temp);
	temp.array[4 * 1 + 1] = cos(angle);
	temp.array[4 * 1 + 2] = -sin(angle);
	temp.array[4 * 2 + 1] = sin(angle);
	temp.array[4 * 2 + 2] = cos(angle);
	return (matrix_tuple_multi(&temp, tuple));
}

t_tuple	rot_y(t_tuple *tuple, t_fl angle)
{
	t_mtx_4	temp;

	identity_matrix_set(&temp);
	temp.array[4 * 0 + 0] = cos(angle);
	temp.array[4 * 0 + 2] = sin(angle);
	temp.array[4 * 2 + 0] = -sin(angle);
	temp.array[4 * 2 + 2] = cos(angle);
	return (matrix_tuple_multi(&temp, tuple));
}

t_tuple	rot_z(t_tuple *tuple, t_fl angle)
{
	t_mtx_4	temp;

	identity_matrix_set(&temp);
	temp.array[4 * 0 + 0] = cos(angle);
	temp.array[4 * 0 + 1] = -sin(angle);
	temp.array[4 * 1 + 0] = sin(angle);
	temp.array[4 * 1 + 1] = cos(angle);
	return (matrix_tuple_multi(&temp, tuple));
}

t_ray	ray_translation(t_ray ray, t_tuple transform)
{
	t_ray	new;

	new.origin = translate(&ray.origin, &transform);
	new.direction = ray.direction;
	return (new);
}

t_ray	ray_scale(t_ray ray, t_tuple transform)
{
	t_ray	new;

	new.origin = scale(&ray.origin, &transform);
	new.direction = scale(&ray.direction, &transform);
	return (new);
}

/*t_mtx_4	*translate(t_tuple tuple, t_mtx_4 *transform, t_tuple vector)
{
	transform->array[3] = vector.tuple.x_width;
	transform->array[7] = vector.tuple.y_height;
	transform->array[11] = vector.tuple.z_depth;
	return (transform);
}*/
