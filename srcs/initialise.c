/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:03:00 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/14 16:50:08 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	background_colour(t_win *win)
{
	int		x;
	int		y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			img_pixel_put(win, x, y, 0x40E0D0U);
		}
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
}

void	initialise_image(t_img *img, t_win *win)
{
	img->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	// if (!img->img)
	// 	handle_errors(win);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->length, \
	&img->endian);
}

void	initialise_window(t_win *win)
{
	// win->mlx = mlx_init();
	// if (!win->mlx)
	// 	handle_errors(win);
	// win->win = mlx_new_window(win->mlx, WIDTH, HEIGHT, "RTV1");
	// if (!win->win)
	// 	handle_errors(win);
	// initialise_image(&win->img, win);
	background_colour(win);
}

void	identity_matrix_set(t_mtx_4 *dst)
{
	dst->array[MATRIX_FOUR_BY_FOUR_ROW_0__COL_0] = 1.0;
	dst->array[MATRIX_FOUR_BY_FOUR_ROW_1__COL_1] = 1.0;
	dst->array[MATRIX_FOUR_BY_FOUR_ROW_2__COL_2] = 1.0;
	dst->array[MATRIX_FOUR_BY_FOUR_ROW_3__COL_3] = 1.0;
}
