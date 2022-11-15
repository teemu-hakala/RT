/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:13:29 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/15 10:13:31 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	render(t_win *win, t_camera *camera)
{
	t_canvas	canvas;
	t_tuple		colour;

	canvas.vertical = 0;
	while (canvas.vertical < camera->size.vertical)
	{
		canvas.horizontal = 0;
		while (canvas.horizontal < camera->size.horizontal)
		{
			win->world.ray = ray_for_pixel(camera, (t_canvas){.vertical = \
				canvas.vertical, .horizontal = canvas.horizontal});
			colour = colour_at(&win->world);
			img_pixel_put(win, canvas.horizontal, canvas.vertical,
				argb_to_hex(&colour.tuple.colour));
			canvas.horizontal++;
		}
		canvas.vertical++;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
}
