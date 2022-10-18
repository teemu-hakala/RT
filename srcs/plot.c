/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:40:28 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/18 16:20:59 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void plot_points(t_win *win, t_object sphere)
{
	int			x;
	int			y;
	int			world_y;
	int			world_x;
	int			i;
	t_tuple		position;
	t_tuple		ray;
	t_intersections *array;

	y = -1;
	while (++y < HEIGHT)
	{
		world_y = (7/2) - (7/HEIGHT) * y;
		x = -1;
		while (++x < WIDTH)
		{
			world_x = (7/2) + (7/WIDTH) * x;
			position = point(world_x, world_y, 10);
			ray.origin = (t_units){ 0.0, 0.0, -0.5, 1};
			ray.direction = tuple_sub(position, ray_origin);
			sphere_intersect(ray, object_sphere, array);
			i = -1;
			while (++i < array.num)
			{
				if (array.intersections[i].hit == 1)
					img_pixel_put(win, x, y, red);
			}
		}
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
}