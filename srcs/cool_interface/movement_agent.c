/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_agent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:20:24 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 11:20:26 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	camera_upwards(t_win *win, t_fl magnitude)
{
	(void)magnitude;
	win->input.mouse.mode = CAMERA_UP;
	win->world.camera.transform.translation.tuple.units.y += magnitude;
	// win->world.camera.origin.tuple.units.y += magnitude;
	win->world.camera.center_of_interest.array[Y] += magnitude;
	// transform_camera(&win->world.camera);
	transform_camera(&win->world.camera);
}

void	camera_forwards(t_win *win, t_fl magnitude)
{
	t_tuple	difference;


	(void)magnitude;
	win->input.mouse.mode = CAMERA_FORWARD;
	difference = tuple_sub(win->world.camera.center_of_interest, \
		win->world.camera.origin);
	difference = tuple_scale(difference, magnitude);
	win->world.camera.origin = tuple_add(win->world.camera.origin, \
		difference);
	win->world.camera.center_of_interest = \
		tuple_add(win->world.camera.center_of_interest, difference);
	transform_camera(&win->world.camera);
}

void	camera_sideways(t_win *win, t_fl magnitude)
{
	t_tuple		difference;
	t_tuple		left;

	(void)magnitude;
	win->input.mouse.mode = CAMERA_LEFT;
	difference = tuple_sub(win->world.camera.center_of_interest, \
		win->world.camera.origin);
	left = cross_product(difference, vector(0, 1, 0));
	if (tuple_nearly_equals(left, vector(0, 0, 0)))
		left = cross_product(difference, vector(0, 0, 1));
	left = tuple_scale(normalize(left), magnitude);
	win->world.camera.origin = tuple_add(win->world.camera.origin, left);
	win->world.camera.center_of_interest = \
		tuple_add(win->world.camera.center_of_interest, left);
	transform_camera(&win->world.camera);
}

void	movement_agent(t_win *win, int key)
{
	if (key == KEY_Q)
		camera_upwards(win, UP_STEP);
	else if (key == KEY_W)
		camera_forwards(win, FORWARD_STEP);
	else if (key == KEY_E)
		camera_upwards(win, -UP_STEP);
	else if (key == KEY_A)
		camera_sideways(win, LEFT_STEP);
	else if (key == KEY_S)
		camera_forwards(win, -FORWARD_STEP);
	else if (key == KEY_D)
		camera_sideways(win, -LEFT_STEP);
	refresh_image(win);
}
