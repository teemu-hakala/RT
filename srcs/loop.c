











#include "RT.h"
#include <stdio.h>

void	render_y_x(t_win *win, t_camera *camera, uint16_t y, uint16_t x)
{
	t_canvas	canvas;
	t_tuple		colour;

	canvas.vertical = y;
	canvas.horizontal = x;
	win->world.ray = ray_for_pixel(camera, canvas);
	colour = colour_at(&win->world);
	img_pixel_put(win, canvas.horizontal, canvas.vertical,
		clamped_rgb_to_hex(&colour.tuple.colour));
}

int	incremental_loop(t_win *win)
{
	static t_canvas	canvas = (t_canvas){.horizontal = 0, .vertical = 0};
	static uint64_t	pixel = 0;

	render_y_x(win, &win->world.camera, canvas.vertical, canvas.horizontal++);
	if (++pixel > win->world.camera.canvas.horizontal)
	{
		canvas.vertical++;
		canvas.horizontal = 0;
		pixel = 0;
		if (canvas.vertical % 11 == 0)
		{
			mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
			printf("[%hu, %hu]\n", canvas.vertical, canvas.horizontal);
		}
	}
	return (0);
}
