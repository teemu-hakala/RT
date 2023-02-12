/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_person_camera.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:19:25 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/11 17:45:55 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	first_person_camera(t_win *win)
{
	t_tuple			*rotation;
	t_mtx			matrix;

	rotation = &win->world.camera.transform.rotation;
	matrix = identity_matrix();
	rotation->array[X] += win->input.mouse.diff.row * win->rotation_step;
	rotation->array[Y] += win->input.mouse.diff.col * win->rotation_step;
	rot_y(&matrix, rotation->array[Y]);
	rot_x(&matrix, rotation->array[X]);
	win->world.camera.center_of_interest = \
		tuple_add(matrix_tuple_multi(&matrix, &(t_tuple){{{0, 0, 1, 1}}}), \
		win->world.camera.origin);
	transform_camera(&win->world.camera);
}

void	refresh_image(t_win *win)
{
	t_canvas	c;

	c = win->world.camera.canvas;
	pthread_mutex_lock(&win->drawn_mutex);
	if (win->drawn == false)
	{
		pthread_detach(win->bar_thread);
		pthread_cancel(win->bar_thread);
	}
	win->drawn = false;
	pthread_mutex_unlock(&win->drawn_mutex);
	progress_bar_image(win, \
		&(t_canvas){.horizontal = c.horizontal - 20, \
			.vertical = 20}, BAR_CLEAR);
	pthread_create(&win->bar_thread, NULL, progress_percentage, win);
	threaded_loop(win, win->progress);
	put_keys_image(win);
	mlx_loop_hook(win->mlx, put_image, win);
}

void	navigate_camera(t_win *win)
{
	first_person_camera(win);
	if (win->progress == NULL)
		return ;
	refresh_image(win);
}
