/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:09:40 by deelliot          #+#    #+#             */
/*   Updated: 2022/11/18 14:26:42 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static t_fl	clamp(t_fl min, t_fl clamped, t_fl max)
{
	if (clamped > max)
		return (max);
	else if (clamped < min)
		return (min);
	return (clamped);
}

uint32_t	clamped_rgb_to_hex(t_colour *colour)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	r = 255 * clamp(0, colour->r, 1);
	g = 255 * clamp(0, colour->g, 1);
	b = 255 * clamp(0, colour->b, 1);
	return ((r << 16) | (g << 8) | b);
}

t_tuple	hex_to_tuple_colour(uint32_t colour)
{
	return ((t_tuple){.tuple.colour.r = ((colour >> 16) & 0xFFu) / (t_fl)0xFFu,
		.tuple.colour.g = ((colour >> 8) & 0xFFu) / (t_fl)0xFFu,
		.tuple.colour.b = (colour & 0xFFu) / (t_fl)0xFFu,
		.tuple.colour.w = VECTOR_0});
}

void	img_pixel_put(t_win *win, int x, int y, uint32_t colour)
{
	char	*pixel;

	if (x >= 0 && x < win->world.camera.canvas.horizontal \
		&& y >= 0 && y < win->world.camera.canvas.vertical)
	{
		pixel = win->img.addr + (y * win->img.length + \
			x * (win->img.bpp / 8));
		*(uint32_t *)pixel = colour;
	}
}
