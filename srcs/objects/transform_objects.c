/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:02:57 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/21 14:05:19 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	transform_object(t_transform *object)
{
	identity_matrix_set(&object->matrix);
	translate(&object->matrix, &object->translation);
	rotate(&object->matrix, &object->rotation);
	scale(&object->matrix, &object->scale);
	object->inverse = object->matrix;
	matrix_inversion(&object->inverse, 4);
}

void	transform_camera(t_camera *camera)
{
	t_mtx	view_matrix;

	identity_matrix_set(&camera->transform.matrix);
	translate(&camera->transform.matrix, &camera->transform.translation);
	rotate(&camera->transform.matrix, &camera->transform.rotation);
	scale(&camera->transform.matrix, &camera->transform.scale);
	camera->origin = matrix_tuple_multi(&camera->transform.matrix, &camera->origin);
	view_matrix = view_transform(camera->origin, camera->center_of_interest, \
		vector(0, 1, 0));
	camera->transform.inverse = view_matrix;
	matrix_inversion(&camera->transform.inverse, 4);
	camera->pixel_size = get_pixel_size(camera, camera->canvas, \
		camera->field_of_view);
}
