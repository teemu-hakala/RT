/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:40:28 by deelliot          #+#    #+#             */
/*   Updated: 2022/10/23 06:51:31 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void	plot_points(t_win *win, t_object *sphere, t_pt_light light)
{
	t_index			obj_space;
	t_index			world;
	int				i;
	t_tuple			position;
	t_ray			ray;
	t_intersections list;
	t_tuple			lit_point;
	t_phong			vectors;
	uint32_t		final_colour;
	t_tuple			colour_argb;

	// a lot of these variables I image will be in a struct,
	// so it gets passed around instead of having to create them here.

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
			ray.direction = normalize(tuple_sub(position, ray.origin));
			ray.direction = matrix_tuple_multi(&sphere->object.sphere.transform.inverse, &ray.direction);
			sphere_intersection(&ray, sphere, &list, win);
			i = -1;
			while (++i < list.num)
			{
				if (list.intersections[i].hit == 1)
				{
					lit_point = hit_position(&ray, list.intersections[i].time);
					vectors.surface_normal = normal_at_sphere(sphere, &lit_point);
					vectors.eye = tuple_scale(ray.direction, -1.0);
					colour_argb = lighting(sphere->object.sphere.material, light, vectors, lit_point);
					final_colour = argb_to_hex(&colour_argb.tuple.colour);
					img_pixel_put(win, obj_space.col, obj_space.row, final_colour);
				}
			}
			free(list.intersections);
		}
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
}

/*void	plot_points_params(t_win *win)
{
	t_index			obj_space;
	t_index			world;
	int				i;
	t_tuple			position;
	t_ray			ray;
	t_intersections list;
	t_tuple			lit_point;
	t_phong			vectors;
	uint32_t		final_colour;
	t_tuple			colour_argb;

	// a lot of these variables I image will be in a struct,
	// so it gets passed around instead of having to create them here.

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
			ray.direction = normalize(tuple_sub(position, ray.origin));
			sphere_intersection(&ray, sphere, &list, win);
			i = -1;
			while (++i < list.num)
			{
				if (list.intersections[i].hit == 1)
				{
					lit_point = hit_position(&ray, list.intersections[i].time);
					vectors.surface_normal = normal_at(win->scene.objects.list[obj_idx], lit_point);
					vectors.eye = tuple_scale(ray.direction, -1.0);
					colour_argb = lighting(sphere->object.sphere.material, light, vectors, lit_point);
					final_colour = argb_to_hex(&colour_argb.tuple.colour);
					img_pixel_put(win, obj_space.col, obj_space.row, final_colour);
				}
			}
			free(list.intersections);
		}
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
}

void	plot_points_params(t_win *win)
{
	t_index		object_space;
	t_coords	world_space;
	uint64_t	obj_idx;


	object_space.row = -1;
	while (++object_space.row < HEIGHT)
	{
		world_space.row = (t_fl)WALL_HEIGHT / 2 - WALL_HEIGHT / HEIGHT * (t_fl)object_space.row;
		object_space.col = -1;
		while (++object_space.col < WIDTH)
		{
			world_space.col = (t_fl)WALL_WIDTH / 2 - WALL_WIDTH / WIDTH * (t_fl)object_space.col;
			obj_idx = -1;
			while (++obj_idx < win->scene.objects.count)
			{
				intersect(win->scene.objects.list[obj_idx]);
			}
		}
	}
}*/
