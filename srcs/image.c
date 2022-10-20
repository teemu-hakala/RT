/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 16:32:35 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/20 16:48:43 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"


// unsigned int argb_to_hex(t_tuple colour)
// {
// 	(void)colour;
// }

void	img_pixel_put(t_win *win, int x, int y, t_tuple *colour)
{
	// char	*pixel;

	// if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	// {
	// 	pixel = win->img.addr + (y * win->img.length + \
	// 		x * (win->img.bpp / 8));
	// 	*(unsigned int *)pixel = colour;
	// }

	int	pix;

	pix = (y * win->img.length) + (x * win->img.bpp / 8);
	if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))
	{
		win->img.addr[pix + 0] = colour->tuple.colour.r;
		win->img.addr[pix + 1] = colour->tuple.colour.g;
		win->img.addr[pix + 2] = colour->tuple.colour.b;
	}
}
