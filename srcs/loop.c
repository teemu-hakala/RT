











#include "RT.h"
#include <stdio.h>

void	render_n_pixels(t_win *win, t_camera *camera, t_canvas from, \
	uint64_t pixels)
{
	t_canvas	canvas;
	t_tuple		colour;

	canvas.vertical = from.vertical;
	canvas.horizontal = from.horizontal;
	while (canvas.vertical < camera->canvas.vertical)
	{
		while (canvas.horizontal < camera->canvas.horizontal)
		{
			win->world.ray = ray_for_pixel(camera, canvas);
			colour = colour_at(&win->world);
			img_pixel_put(win, canvas.horizontal, canvas.vertical,
				clamped_rgb_to_hex(&colour.tuple.colour));
			canvas.horizontal++;
			if (--pixels == 0)
				return ;
		}
		canvas.horizontal = 0;
		canvas.vertical++;
	}
}

static t_img	progress_bar_image(t_win *win, t_canvas *bar_dimensions)
{
	static t_img	bar_img = {};
	t_rectangle		filler;

	if (bar_img.img == NULL)
	{
		bar_img.img = mlx_new_image(win->mlx, \
			bar_dimensions->horizontal, bar_dimensions->vertical);
		if (bar_img.img == NULL)
			handle_errors("bar_img.img got NULL");
		bar_img.addr = mlx_get_data_addr(bar_img.img, &bar_img.bpp, \
			&bar_img.length, &bar_img.endian);
		if (bar_img.addr == NULL)
			handle_errors("bar_img.addr got NULL");
		filler = (t_rectangle){{}, *bar_dimensions};
		put_rectangle_to_image(bar_img, filler, filler, (t_tuple){.tuple.colour = {0, 0, 0, 1}});
	}
	return (bar_img);
}

int	incremental_loop(t_win *win)
{
	static t_canvas	canvas = (t_canvas){.horizontal = 0, .vertical = 0};

	if (canvas.vertical > win->world.camera.canvas.vertical)
	{
		//mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
		printf("asd\n");
		mlx_loop_hook(win->mlx, NULL, NULL);
		return (0);
	}
	render_n_pixels(win, &win->world.camera, canvas, WIDTH * 1);
	progress_bar(progress_bar_image(win, &(t_canvas){.horizontal = WIDTH - 20, .vertical = 20}), (t_fl)canvas.vertical / \
		win->world.camera.canvas.vertical);
	canvas.vertical += 1;
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
	mlx_put_image_to_window(win->mlx, win->win, progress_bar_image(win, NULL).img, 10, HEIGHT / 2 - 10);
	// printf("[%hu, %hu]\n", canvas.vertical, canvas.horizontal);
	return (0);
}
