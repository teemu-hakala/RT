










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

void	*render_n_pixels(void *param)
{
	t_canvas		canvas;
	t_tuple			colour;
	t_renderer_info	renderer_info;
	t_world			world_safe;

	renderer_info = *(t_renderer_info *)param;
	world_safe = world_selectively_shallow_copy(&renderer_info.win->world);
	canvas.vertical = renderer_info.from.vertical;
	canvas.horizontal = renderer_info.from.horizontal;
	while (canvas.vertical < renderer_info.camera->canvas.vertical)
	{
		while (canvas.horizontal < renderer_info.camera->canvas.horizontal)
		{
			//printf("%li: [%hu, %hu]\n", (long)renderer_info.thread_id, canvas.vertical, canvas.horizontal);
			world_safe.ray = ray_for_pixel(renderer_info.camera, canvas);
			colour = colour_at(&world_safe);
			img_pixel_put(renderer_info.win, canvas.horizontal, canvas.vertical,
				clamped_rgb_to_hex(&colour.tuple.colour));
			canvas.horizontal++;
			if (--renderer_info.pixels == 0)
				return (world_end(&world_safe));
		}
		canvas.horizontal = 0;
		canvas.vertical++;
	}
	return (NULL);
}
# define THREAD_COUNT 12
# define PIXEL_COUNT ((WIDTH * HEIGHT) / THREAD_COUNT)

void	threaded_loop(t_win *win)
{
	pthread_t				thread_id[THREAD_COUNT];
	static t_renderer_info	renderer_info[THREAD_COUNT];
	uint16_t				thread_count;
	t_canvas_64				from;

	from = (t_canvas_64){.vertical = 0, .horizontal = 0};
	thread_count = 0;
	while (thread_count < THREAD_COUNT)
	{
		renderer_info[thread_count] = (t_renderer_info){.win = win, \
			.camera = &win->world.camera, .from = from, .pixels = PIXEL_COUNT, \
			.thread_id = thread_id[thread_count]};
		pthread_create(&thread_id[thread_count], NULL, render_n_pixels, \
			&renderer_info[thread_count]);
		from.horizontal += PIXEL_COUNT;
		from.vertical += from.horizontal / win->world.camera.canvas.horizontal;
		from.horizontal %= win->world.camera.canvas.horizontal;
		thread_count++;
	}
}
