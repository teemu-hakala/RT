/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thakala <thakala@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:00:02 by deelliot          #+#    #+#             */
/*   Updated: 2023/02/12 17:44:41 by thakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RT.h"

t_world	world_selectively_shallow_copy(t_world *original)
{
	t_world		copy;

	copy = (t_world){.camera = original->camera, .lights = original->lights, \
		.objects = original->objects, .filter = original->filter};
	if (vec_new(&copy.intersections, 1, sizeof(t_intersect))
		!= VEC_SUCCESS)
		handle_errors("world_selectively_shallow_copy malloc returned NULL");
	return (copy);
}

void	*world_end(t_world *ending_world, pthread_mutex_t *progress_mutex)
{
	free(ending_world->intersections.memory);
	ending_world->intersections.memory = NULL;
	pthread_mutex_unlock(progress_mutex);
	pthread_detach(pthread_self());
	pthread_exit(NULL);
	return (NULL);
}

void	*render_norme(t_norme_render r)
{
	t_tuple			colour;

	r.world_safe->ray = ray_for_pixel(r.info->camera, r.canvas);
	r.world_safe->lifetime = 5;
	r.world_safe->refraction_lifetime = 5;
	colour = colour_at(r.world_safe, r.world_safe->ray);
	if (r.info->frame != *r.info->current_frame)
		return (world_end(r.world_safe, &r.info->progress->mutex));
	img_pixel_put(r.info->win, r.canvas.horizontal, r.canvas.vertical,
		clamped_rgb_to_hex(&colour.tuple.colour));
	pthread_mutex_lock(&r.info->progress->mutex);
	r.info->progress->pixels += r.info->frame == r.info->progress->frame;
	if (r.info->frame != r.info->progress->frame \
		|| r.info->progress->pixels >= r.info->pixels)
		return (world_end(r.world_safe, &r.info->progress->mutex));
	pthread_mutex_unlock(&r.info->progress->mutex);
	return ((void *)1);
}

void	*render_n_pixels(void *param)
{
	t_canvas		canvas;
	t_renderer_info	info;
	t_world			world_safe;
	t_norme_render	norme_render;

	info = *(t_renderer_info *)param;
	info.pixels += !!info.is_last * info.win->remaining_pixels;
	world_safe = world_selectively_shallow_copy(&info.win->world);
	canvas = (t_canvas){info.from.vertical - 1, info.from.horizontal};
	pthread_mutex_lock(&info.progress->mutex);
	info.progress->pixels = 0;
	pthread_mutex_unlock(&info.progress->mutex);
	while (++canvas.vertical < info.camera->canvas.vertical)
	{
		while (canvas.horizontal < info.camera->canvas.horizontal)
		{
			norme_render = (t_norme_render){.info = &info, .canvas = canvas,
				.world_safe = &world_safe};
			if (render_norme(norme_render) != (void *)1)
				return (NULL);
			canvas.horizontal++;
		}
		canvas.horizontal = 0;
	}
	return (world_end(&world_safe, &info.progress->mutex));
}

void	threaded_loop(t_win *win, t_progress progress[THREAD_COUNT])
{
	static pthread_t		thread_id[THREAD_COUNT];
	static t_renderer_info	renderer_info[THREAD_COUNT];
	uint16_t				thread_count;
	t_canvas_64				from;
	static uint64_t			frame = 0;

	frame++;
	clear_progress(progress, frame);
	from = (t_canvas_64){.vertical = 0, .horizontal = 0};
	thread_count = 0;
	while (thread_count < THREAD_COUNT)
	{
		renderer_info[thread_count] = (t_renderer_info){.win = win, \
			.camera = &win->world.camera, .from = from, .pixels = win->pixels, \
			.thread_id = thread_id[thread_count], .frame = frame, \
			.current_frame = &frame, .progress = &progress[thread_count], \
			.is_last = thread_count == THREAD_COUNT - 1};
		pthread_create(&thread_id[thread_count], NULL, render_n_pixels, \
			&renderer_info[thread_count]);
		from.horizontal += win->pixels;
		from.vertical += from.horizontal / win->world.camera.canvas.horizontal;
		from.horizontal %= win->world.camera.canvas.horizontal;
		thread_count++;
	}
}
