/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:19:16 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 11:19:20 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_fl	get_pixel_size(t_camera *camera, t_canvas size, t_fl field_of_view)
{
	t_fl		half_view;
	t_fl		aspect;

	half_view = (t_fl)tan(field_of_view / 2);
	aspect = (t_fl)size.horizontal / (t_fl)size.vertical;
	if (aspect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	return ((camera->half_width * 2) / size.horizontal);
}

t_camera	camera_prototype(void)
{
	t_camera	camera;

	camera.origin = point(0, 0, -5);
	camera.transform = default_transform_1();
	camera.center_of_interest = point(0, 0, 0);
	camera.field_of_view = M_2_PI;
	camera.canvas = default_canvas();
	camera.pixel_size = get_pixel_size(&camera, camera.canvas, \
		camera.field_of_view);
	transform_camera(&camera);
	return (camera);
}
