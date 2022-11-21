/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:13:17 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/21 15:04:56 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_ray	ray_transform(t_ray *ray, t_mtx *transform)
{
	t_ray	result;

	result.origin = matrix_tuple_multi(transform, &ray->origin);
	result.direction = matrix_tuple_multi(transform, &ray->direction);
	return (result);
}

t_ray	ray_for_pixel(t_camera *camera, t_canvas position)
{
	t_index	offset;
	t_index	world;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;

	offset = (t_index){.row = (position.vertical + 0.5) * camera->pixel_size, \
		.col = (position.horizontal + 0.5) * camera->pixel_size};
	world = (t_index){.row = camera->half_height - offset.row, \
		.col = camera->half_width - offset.col};
	pixel = point(world.col, world.row, -1);
	pixel = matrix_tuple_multi(&camera->transform.inverse, &pixel);
	origin = point(0, 0, 0);
	origin = matrix_tuple_multi(&camera->transform.inverse, &origin);
	direction = normalize(tuple_sub(pixel, origin));
	return ((t_ray){.origin = origin, .direction = direction});
}
