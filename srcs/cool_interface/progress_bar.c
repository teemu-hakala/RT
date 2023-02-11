/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 11:20:40 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/11 17:09:00 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

# 	 include	 	 <stdio.h>

t_img	progress_bar_image(t_win *win, t_canvas *bar_dimensions, uint8_t flag)
{
	static t_img		bar_img = {};
	static t_rectangle	filler = {};

	if (bar_img.img == NULL)
	{
		printf("bar_img.img == NULL\n");
		bar_img.dimensions = (t_rectangle){{}, *bar_dimensions, {}};
		bar_img.img = mlx_new_image(win->mlx, \
			bar_dimensions->horizontal, bar_dimensions->vertical);
		if (bar_img.img == NULL)
			handle_errors("bar_img.img got NULL");
		bar_img.addr = mlx_get_data_addr(bar_img.img, &bar_img.bpp, \
			&bar_img.length, &bar_img.endian);
		if (bar_img.addr == NULL)
			handle_errors("bar_img.addr got NULL");
		filler = (t_rectangle){{}, *bar_dimensions, {}};
	}
	printf("t_rectangle filler: start [y, x] [%u, %u], end [y, x] [%u, %u]\n", filler.start.vertical, filler.start.horizontal, filler.end.vertical, filler.end.horizontal);
	printf("t_rectangle filler: start [y, x] [%u, %u], end [y, x] [%u, %u]\n", filler.start.vertical, filler.start.horizontal, filler.end.vertical, filler.end.horizontal);
	if (flag & BAR_CLEAR || bar_img.img == NULL)
		put_rectangle_to_image(bar_img, filler, filler, \
			(t_tuple){.tuple.colour = {0, 0, 0, 1}});
	return (bar_img);
}

static void	rect_pixel_put(t_img img, int y, int x, uint32_t colour)
{
	char	*pixel;

	printf("[y, x] === [%i, %i]\n", y, x);
	pixel = img.addr + (y * img.length + x * (img.bpp / 8));
	*(uint32_t *)pixel = colour;
}

static void	fit_rectangle_to_image_bounds(t_rectangle *rect,
	t_rectangle image)
{
	if (rect->start.horizontal != image.start.horizontal)
		rect->start.horizontal = image.start.horizontal;
	if (rect->start.vertical != image.start.vertical)
		rect->start.vertical = image.start.vertical;
	if (rect->end.horizontal != image.end.horizontal)
		rect->end.horizontal = image.end.horizontal;
	if (rect->end.vertical != image.end.vertical)
		rect->end.vertical = image.end.vertical;
}

void	put_rectangle_to_image(t_img img, t_rectangle image,
	t_rectangle rect, t_tuple colour)
{
	uint32_t	colour_hex;
	t_canvas	point;

	printf("t_rectangle image: start [y, x] [%u, %u], end [y, x] [%u, %u]\n", image.start.vertical, image.start.horizontal, image.end.vertical, image.end.horizontal);
	colour_hex = clamped_rgba_to_hex(&colour.tuple.colour);
	fit_rectangle_to_image_bounds(&rect, image);
	point.vertical = rect.start.vertical;
	while (point.vertical < rect.end.vertical)
	{
		point.horizontal = rect.start.horizontal;
		printf("rect.end.horizontal: %u\n", rect.end.horizontal);
		while (point.horizontal < rect.end.horizontal)
		{
			rect_pixel_put(img, point.vertical, point.horizontal, colour_hex);
			point.horizontal++;
		}
		if (point.vertical == 19)
			printf("asd\n");
		point.vertical++;
	}
}

void	progress_bar(t_img img, t_fl progress_percentage, t_fl prev_perc)
{
	t_rectangle	image_bounds;
	t_rectangle	rectangle;
	t_tuple		colour;

	printf("t_rectangle img.dimensions start [y,x] [%u, %u], end [y,x] [%u, %u]\n", img.dimensions.start.vertical, img.dimensions.start.horizontal, img.dimensions.end.vertical, img.dimensions.end.horizontal);
	image_bounds = (t_rectangle){.start = {.horizontal = \
		(img.dimensions.end.horizontal - 20) * \
		prev_perc, .vertical = 0}, \
		.end = {.horizontal = img.dimensions.end.horizontal - 20, \
		.vertical = 20}};
	rectangle = (t_rectangle){.start = {.horizontal = progress_percentage, \
		.vertical = 0}, \
		.end = {.horizontal = (img.dimensions.end.horizontal - 20) \
			* progress_percentage + 10, \
		.vertical = 20}};
	if (prev_perc == 0)
		rectangle.start.horizontal = 0;
	colour = (t_tuple){.tuple.colour = {.r = progress_percentage, \
		.g = progress_percentage, .b = 1, .a = 0}};
	put_rectangle_to_image(img, image_bounds, rectangle, colour);
}
