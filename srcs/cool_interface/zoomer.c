/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoomer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:20:54 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/11 17:50:14 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	field_of_view_delta(t_win *win, t_fl step)
{
	win->input.mouse.mode = CAMERA_FOV;
	win->world.camera.field_of_view += step;
	transform_camera_for_field_of_view(&win->world.camera);
}

void	handle_key_compounding(t_win *win, int8_t direction)
{
	if (win->input.mouse.mode != CAMERA_FOV)
	{
		win->input.mouse.mode = CAMERA_FOV;
		win->input.mouse.compounder = (t_compounder){.compounds = 1, \
			.direction = direction, .mode = CAMERA_FOV};
	}
	else if (win->input.mouse.compounder.direction != direction)
	{
		if (win->input.mouse.compounder.compounds == 0)
			win->input.mouse.compounder.compounds = 1;
		else if (win->input.mouse.compounder.compounds > 1)
			win->input.mouse.compounder.compounds -= 1;
		win->input.mouse.compounder.direction = direction;
	}
	else
		win->input.mouse.compounder.compounds += 1;
}

void	field_of_view_zoomer(t_win *win, int key)
{
	if (key == KEY_R)
	{
		handle_key_compounding(win, POSITIVE_DIRECTION);
		field_of_view_delta(win, ZOOM_STEP \
			* win->input.mouse.compounder.compounds);
	}
	else if (key == KEY_F)
	{
		handle_key_compounding(win, NEGATIVE_DIRECTION);
		field_of_view_delta(win, -ZOOM_STEP \
			* win->input.mouse.compounder.compounds);
	}
	refresh_image(win);
}
