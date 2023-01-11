










#include <stdio.h>
#include "RT.h"

t_world	world_selectively_shallow_copy(t_world *original)
{
	t_world		copy;

	copy = (t_world){.camera = original->camera, .lights = original->lights, \
		.objects = original->objects};
	if (vec_new(&copy.intersections, 1, sizeof(t_intersect))
		!= VEC_SUCCESS)
		handle_errors("world_selectively_shallow_copy malloc returned NULL");
	return (copy);
}

void	*world_end(t_world *ending_world)
{
	free(ending_world->intersections.memory);
	return (NULL);
}

void	darken_n_pixels(t_renderer_info info, t_canvas to)
{
	t_canvas	canvas;

	canvas.vertical = info.from.vertical;
	canvas.horizontal = info.from.horizontal;
	while (canvas.vertical < to.vertical)
	{
		while (canvas.horizontal < to.horizontal)
		{
			img_pixel_put(info.win, canvas.horizontal, canvas.vertical,
				0xffff0000);
			canvas.horizontal++;
		}
		canvas.horizontal = 0;
		canvas.vertical++;
	}
}

void	*render_n_pixels(void *param)
{
	t_canvas		canvas;
	t_tuple			colour;
	t_renderer_info	info;
	t_world			world_safe;

	info = *(t_renderer_info *)param;
	world_safe = world_selectively_shallow_copy(&info.win->world);
	canvas.vertical = info.from.vertical;
	canvas.horizontal = info.from.horizontal;
	pthread_mutex_lock(&info.progress->mutex);
	info.progress->pixels = 0;
	while (canvas.vertical < info.camera->canvas.vertical)
	{
		while (canvas.horizontal < info.camera->canvas.horizontal)
		{
			pthread_mutex_unlock(&info.progress->mutex);
			world_safe.ray = ray_for_pixel(info.camera, canvas);
			colour = colour_at(&world_safe);
			if (info.frame != *info.current_frame)
			{
				//darken_n_pixels(info, canvas);
				world_end(&world_safe);
				pthread_exit(NULL);
				return (NULL);
			}
			img_pixel_put(info.win, canvas.horizontal, canvas.vertical,
				clamped_rgb_to_hex(&colour.tuple.colour));
			canvas.horizontal++;
			pthread_mutex_lock(&info.progress->mutex);
			info.progress->pixels += info.frame == info.progress->frame;
			if (info.frame != info.progress->frame \
				|| info.progress->pixels >= info.pixels)
			{
				world_end(&world_safe);
				pthread_mutex_unlock(&info.progress->mutex);
				return (NULL);
			}
		}
		canvas.horizontal = 0;
		canvas.vertical++;
	}
	pthread_mutex_unlock(&info.progress->mutex);
	return (NULL);
}

void	threaded_loop(t_win *win, t_progress progress[THREAD_COUNT])
{
	static pthread_t		thread_id[THREAD_COUNT];
	static t_renderer_info	renderer_info[THREAD_COUNT];
	uint16_t				thread_count;
	t_canvas_64				from;
	static uint64_t			frame = 0;

	//mlx_clear_window(win->mlx, win->win);
	frame++;
	clear_progress(progress, frame);
	from = (t_canvas_64){.vertical = 0, .horizontal = 0};
	thread_count = 0;
	while (thread_count < THREAD_COUNT - 1)
	{
		renderer_info[thread_count] = (t_renderer_info){.win = win, \
			.camera = &win->world.camera, .from = from, .pixels = PIXEL_COUNT, \
			.thread_id = thread_id[thread_count], .frame = frame, \
			.current_frame = &frame, .progress = &progress[thread_count]};
		pthread_create(&thread_id[thread_count], NULL, render_n_pixels, \
			&renderer_info[thread_count]);
		from.horizontal += PIXEL_COUNT;
		from.vertical += from.horizontal / win->world.camera.canvas.horizontal;
		from.horizontal %= win->world.camera.canvas.horizontal;
		thread_count++;
	}
	renderer_info[thread_count] = (t_renderer_info){.win = win, \
		.camera = &win->world.camera, .from = from, .pixels = PIXEL_COUNT + \
		REMAINING_PIXELS, .thread_id = thread_id[thread_count], .frame = \
		frame, .current_frame = &frame, .progress = &progress[thread_count]};
	pthread_create(&thread_id[thread_count], NULL, render_n_pixels, \
		&renderer_info[thread_count]);
}
