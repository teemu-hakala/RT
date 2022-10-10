/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:32:35 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/09 17:45:01 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/RTv1.h"

void	img_pixel_put(t_win *win, int x, int y, int colour)
{
	char	*pixel;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		pixel = win->img.addr + (y * win->img.length + \
			x * (win->img.bpp / 8));
		*(unsigned int *)pixel = colour;
	}

	// int	pix;

	// pix = (y * win->img.length) + (x * win->img.bpp / 8);
	// if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))
	// {
	// 	win->img.addr[pix + 0] = colour.r;
	// 	win->img.addr[pix + 1] = colour.g;
	// 	win->img.addr[pix + 2] = colour.b;
	// }
}
