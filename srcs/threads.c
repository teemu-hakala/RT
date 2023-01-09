










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

static uint64_t	match_frame(t_frame_check mode, uint64_t frame)
{
	static uint64_t	current_frame = 0;

	if (mode & FRAME_NEXT)
		return (++current_frame);
	return (frame == current_frame);
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
	while (canvas.vertical < info.camera->canvas.vertical)
	{
		while (canvas.horizontal < info.camera->canvas.horizontal)
		{
			//printf("%li: [%hu, %hu]\n", (long)info.thread_id, canvas.vertical, canvas.horizontal);
			world_safe.ray = ray_for_pixel(info.camera, canvas);
			colour = colour_at(&world_safe);
			if (!match_frame(FRAME_CHECK, info.frame))
			{
				// img_pixel_put(info.win, canvas.horizontal, canvas.vertical,
				// 	0x00ff0000u); //debug pixel at the end of thread?
				world_end(&world_safe);
				// pthread_kill(pthread_self(), SIGKILL);
				//printf("%li : %li\n", (long)info.thread_id, (long)pthread_self());
				if (pthread_equal(info.thread_id, pthread_self()))
					printf("equals\n");
				pthread_exit(NULL);
				// pthread_detach(pthread_self());
				// pthread_kill(info.thread_id, SIGKILL);
				return (NULL);
			}
			img_pixel_put(info.win, canvas.horizontal, canvas.vertical,
				clamped_rgb_to_hex(&colour.tuple.colour));
			canvas.horizontal++;
			if (--info.pixels == 0)
			{
				world_end(&world_safe);
				return (NULL);
			}
		}
		canvas.horizontal = 0;
		canvas.vertical++;
	}
	return (NULL);
}
# define THREAD_COUNT 64
# define PIXEL_COUNT ((WIDTH * HEIGHT) / THREAD_COUNT)

void	threaded_loop(t_win *win)
{
	pthread_t				thread_id[THREAD_COUNT];
	static t_renderer_info	renderer_info[THREAD_COUNT];
	uint16_t				thread_count;
	t_canvas_64				from;
	uint64_t				frame;

	frame = match_frame(FRAME_NEXT, 0);
	//mlx_clear_window(win->mlx, win->win);
	from = (t_canvas_64){.vertical = 0, .horizontal = 0};
	thread_count = 0;
	while (thread_count < THREAD_COUNT)
	{
		renderer_info[thread_count] = (t_renderer_info){.win = win, \
			.camera = &win->world.camera, .from = from, .pixels = PIXEL_COUNT, \
			.thread_id = thread_id[thread_count], .frame = frame};
		pthread_create(&thread_id[thread_count], NULL, render_n_pixels, \
			&renderer_info[thread_count]);
		from.horizontal += PIXEL_COUNT;
		from.vertical += from.horizontal / win->world.camera.canvas.horizontal;
		from.horizontal %= win->world.camera.canvas.horizontal;
		thread_count++;
	}
}
