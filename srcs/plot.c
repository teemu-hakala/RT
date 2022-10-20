/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:40:28 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/20 16:41:32 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	plot_points(t_win *win, t_object *sphere, t_pt_light *light)
{
	t_coords		obj_space;
	t_coords		world;
	int				i;
	t_tuple			position;
	t_ray			ray;
	t_intersections list;
	t_tuple			temp;
	t_tuple			lit_point;
	t_phong			vectors;

	obj_space.row = -1;
	while (++obj_space.row < HEIGHT)
	{
		world.row = ((t_fl)7 / (t_fl)2) - ((t_fl)7 / (t_fl)HEIGHT) * (t_fl)obj_space.row;
		obj_space.col = -1;
		while (++obj_space.col < WIDTH)
		{
			world.col = ((t_fl)7 / (t_fl)2) - ((t_fl)7 / (t_fl)WIDTH) * (t_fl)obj_space.col;
			position = point(world.col, world.row, 10);
			ray.origin = (t_tuple){.tuple.units = (t_units){0.0, 0.0, -5.0, 1}};
			temp = tuple_sub(&position, &ray.origin);
			ray.direction = normalize(&temp);
			sphere_intersection(&ray, sphere, &list, win);
			i = -1;
			while (++i < list.num)
			{
				if (list.intersections[i].hit == 1)
				{
					lit_point = hit_position(&ray, list.intersections[i].time);
					vectors.surface_normal = normal_at_sphere(&sphere->object.sphere, &lit_point);
					vectors.eye = ray.direction;
					lighting(&sphere->object.sphere.material, light, &vectors, &lit_point);
					img_pixel_put(win, obj_space.col, obj_space.row, &sphere->object.sphere.material.colour);
				}

			}
		}
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
}