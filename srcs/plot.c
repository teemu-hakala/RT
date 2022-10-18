/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:40:28 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/18 22:34:15 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	plot_points(t_win *win, t_object *sphere)
{
	int				x;
	int				y;
	t_fl			world_y;
	t_fl			world_x;
	int				i;
	t_tuple			position;
	t_ray			ray;
	t_intersections intersections;

	y = -1;
	while (++y < HEIGHT)
	{
		world_y = ((t_fl)7 / (t_fl)2) - ((t_fl)7 / (t_fl)HEIGHT) * (t_fl)y;
		x = -1;
		while (++x < WIDTH)
		{
			world_x = ((t_fl)7 / (t_fl)2) - ((t_fl)7 / (t_fl)WIDTH) * (t_fl)x;
			position = point(world_x, world_y, 10);
			ray.origin = (t_tuple){.tuple.units = (t_units){0.0, 0.0, -5.0, 1}};
			ray.direction = tuple_sub(&position, &ray.origin);
			sphere_intersection(&ray, sphere, &intersections, win);
			i = -1;
			while (++i < intersections.num)
			{
				if (intersections.intersections[i].hit == 1)
					img_pixel_put(win, x, y, COLOUR_RED);//sphere->object.sphere.colour);
			}
		}
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
}