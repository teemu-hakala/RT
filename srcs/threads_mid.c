










#include <stdio.h>
#include "RT.h"

void	*render_n_pixels_mid(void *param)
{
	t_canvas		canvas;
	t_tuple			colour;
	t_renderer_info	info;
	t_world			world_safe;
	int32_t			pixel_number;
	uint16_t		pixel_count;
	int32_t			pixeler;

	info = *(t_renderer_info *)param;
	world_safe = world_selectively_shallow_copy(&info.win->world);
	pixel_number = WIDTH / 2;
	pixel_count = 0;
	canvas.vertical = info.from.vertical;
	while (1)
	{
		if (pixel_number - pixel_count < 0 \
			&& pixel_number + pixel_count > WIDTH)
			break;
		pixeler = pixel_number - pixel_count;
		canvas.horizontal = pixeler;
		if (pixeler > 0)
		{
			world_safe.ray = ray_for_pixel(info.camera, canvas);
			colour = colour_at(&world_safe);
			if (info.frame != *info.current_frame)
			{
				//darken_n_pixels(info, canvas);
				world_end(&world_safe);
				pthread_exit(NULL);
				return (NULL);
			}
			img_pixel_put(info.win, pixeler, info.from.vertical,
				clamped_rgb_to_hex(&colour.tuple.colour));
			if (--info.pixels == 0)
			{
				world_end(&world_safe);
				return (NULL);
			}
		}
		pixeler = pixel_number + pixel_count;
		canvas.horizontal = pixeler;
		if (pixeler < WIDTH)
		{
			world_safe.ray = ray_for_pixel(info.camera, canvas);
			colour = colour_at(&world_safe);
			if (info.frame != *info.current_frame)
			{
				//darken_n_pixels(info, canvas);
				world_end(&world_safe);
				pthread_exit(NULL);
				return (NULL);
			}
			img_pixel_put(info.win, pixeler, info.from.vertical,
				clamped_rgb_to_hex(&colour.tuple.colour));
			if (--info.pixels == 0)
			{
				world_end(&world_safe);
				return (NULL);
			}
		}
		pixel_count++;
	}
	return (NULL);
}

#define ALL_PIXELS (WIDTH * HEIGHT)

void	threaded_loop_mid(t_win *win)
{
	static pthread_t		thread_id[HEIGHT];
	static t_renderer_info	renderer_info[HEIGHT];
	int32_t					thread_number;
	uint16_t				thread_count;
	int32_t					threader;
	t_canvas_64				from;
	static uint64_t			frame = 0;

	//mlx_clear_window(win->mlx, win->win);
	frame++;
	from = (t_canvas_64){.vertical = 0, .horizontal = 0};
	thread_number = HEIGHT / 2;
	thread_count = 0;
	while (1)
	{
		if (thread_number - thread_count < 0 \
			&& thread_number + thread_count > HEIGHT)
			break;
		threader = thread_number - thread_count;
		from = (t_canvas_64){.horizontal = 0, .vertical = threader};
		if (0 < threader)
		{
			renderer_info[threader] = (t_renderer_info){.win = win, \
				.camera = &win->world.camera, .from = from, .pixels = WIDTH, \
				.thread_id = thread_id[threader], .frame = frame, \
				.current_frame = &frame};
			pthread_create(&thread_id[threader], NULL, render_n_pixels_mid, \
				&renderer_info[threader]);
		}
		threader = thread_number + thread_count;
		from = (t_canvas_64){.horizontal = 0, .vertical = threader};
		if (threader < HEIGHT)
		{
			renderer_info[threader] = (t_renderer_info){.win = win, \
				.camera = &win->world.camera, .from = from, .pixels = WIDTH, \
				.thread_id = thread_id[threader], .frame = frame, \
				.current_frame = &frame};
			pthread_create(&thread_id[threader], NULL, render_n_pixels_mid, \
				&renderer_info[threader]);
		}
		thread_count++;
	}
}
