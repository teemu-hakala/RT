










#include <stdio.h>
#include "RT.h"

void	*render_n_pixels(void *param)
{
	t_canvas		canvas;
	t_tuple			colour;
	t_renderer_info	renderer_info;

	renderer_info = *(t_renderer_info *)param;
	canvas.vertical = renderer_info.from.vertical;
	canvas.horizontal = renderer_info.from.horizontal;
	while (canvas.vertical < renderer_info.camera->canvas.vertical)
	{
		while (canvas.horizontal < renderer_info.camera->canvas.horizontal)
		{
			printf("%li: [%hu, %hu]\n", (long)renderer_info.thread_id, canvas.vertical, canvas.horizontal);
			renderer_info.win->world.ray = ray_for_pixel(renderer_info.camera, canvas);
			colour = colour_at(&renderer_info.win->world);
			img_pixel_put(renderer_info.win, canvas.horizontal, canvas.vertical,
				clamped_rgb_to_hex(&colour.tuple.colour));
			canvas.horizontal++;
			if (--renderer_info.pixels == 0)
				return (NULL);
		}
		canvas.horizontal = 0;
		canvas.vertical++;
	}
	return (NULL);
}
# define THREAD_COUNT 512
# define PIXEL_COUNT 256

void	threaded_loop(t_win *win)
{
	pthread_t				thread_id[THREAD_COUNT];
	static t_renderer_info	renderer_info[THREAD_COUNT];
	uint16_t				thread_count;
	t_canvas				from;

	from = (t_canvas){.vertical = 0, .horizontal = 0};
	thread_count = 0;
	while (thread_count < THREAD_COUNT)
	{
		renderer_info[thread_count] = (t_renderer_info){.win = win, \
			.camera = &win->world.camera, .from = from, .pixels = PIXEL_COUNT, \
			.thread_id = thread_id[thread_count]};
		pthread_create(&thread_id[thread_count], NULL, render_n_pixels, \
			&renderer_info[thread_count]);
		from.horizontal += PIXEL_COUNT % win->world.camera.canvas.horizontal;
		from.vertical += from.horizontal / win->world.camera.canvas.horizontal;
		from.horizontal %= win->world.camera.canvas.horizontal;
		thread_count++;
	}
}
