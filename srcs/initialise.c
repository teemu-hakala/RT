/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deelliot <deelliot@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:00:12 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/03 12:00:14 by deelliot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

void	initialise_image(t_img *img, t_win *win)
{
	t_canvas	dimensions;

	dimensions = (t_canvas){.horizontal = win->world.camera.canvas.horizontal, \
		.vertical = win->world.camera.canvas.vertical};
	img->dimensions = (t_rectangle){.canvas = dimensions, \
		.start = {0, 0}, .end = dimensions};
	img->img = mlx_new_image(win->mlx, dimensions.horizontal, \
		dimensions.vertical);
	if (!img->img)
		handle_errors("error");
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->length, \
		&img->endian);
	if (!img->addr)
		handle_errors("img->addr is NULL");
}

void	initialise_world(t_world *world)
{
	world->camera = camera_prototype();
	if (vec_new(&world->lights, 8, sizeof(t_light)) != VEC_SUCCESS
		|| vec_new(&world->objects, 64, sizeof(t_object)) != VEC_SUCCESS
		|| vec_new(&world->intersections, 256, sizeof(t_intersect))
		!= VEC_SUCCESS)
		handle_errors("initialise_world malloc returned NULL");
	//world->hit.hit_check = false;
	world->lifetime = 5;
	world->refraction_lifetime = 5;
}

void	initialise_window(t_win *win)
{
	t_canvas	c;

	c = win->world.camera.canvas;
	win->mlx = mlx_init();
	if (!win->mlx)
		handle_errors("error");
	win->win = mlx_new_window(win->mlx, c.horizontal, c.vertical, "RT");
	if (!win->win)
		handle_errors("error");
	initialise_image(&win->img, win);
	win->progress = NULL;
	win->drawn = false;
	pthread_mutex_init(&win->drawn_mutex, NULL);
	win->input.mouse.rmb_is_down = false;
	win->pixels = (c.horizontal * c.vertical) / THREAD_COUNT;
	win->remaining_pixels = (c.horizontal * c.vertical - THREAD_COUNT \
		* win->pixels);
	win->rotation_step = M_PI / 448;
	win->input.mouse.mode = MODE_NONE;
	win->keys_image = (t_img){};
	win->keys_visible = false;
	win->input.mouse.compounder = (t_compounder){};
}

void	identity_matrix_set(t_mtx *dst)
{
	dst->tuple_rows[0] = (t_quad_tuple){1.0, 0.0, 0.0, 0.0};
	dst->tuple_rows[1] = (t_quad_tuple){0.0, 1.0, 0.0, 0.0};
	dst->tuple_rows[2] = (t_quad_tuple){0.0, 0.0, 1.0, 0.0};
	dst->tuple_rows[3] = (t_quad_tuple){0.0, 0.0, 0.0, 1.0};
}

t_mtx	identity_matrix(void)
{
	return ((t_mtx){
		.tuple_rows = {
			(t_quad_tuple){1.0, 0.0, 0.0, 0.0}, \
			(t_quad_tuple){0.0, 1.0, 0.0, 0.0}, \
			(t_quad_tuple){0.0, 0.0, 1.0, 0.0}, \
			(t_quad_tuple){0.0, 0.0, 0.0, 1.0}
		}
		});
}
