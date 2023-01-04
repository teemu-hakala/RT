











#include "RT.h"

void	render_y_x(t_win *win, t_camera *camera, uint16_t y, uint16_t x)
{
	t_canvas	canvas;
	t_tuple		colour;

	canvas.vertical = y;
	canvas.horizontal = x;
	win->world.ray = ray_for_pixel(camera, canvas);
	colour = colour_at(&win->world);
}

void	render(t_win *win, t_camera *camera)
{
	t_canvas	canvas;
	t_tuple		colour;

	canvas.vertical = 0;
	while (canvas.vertical < camera->canvas.vertical)
	{
		canvas.horizontal = 0;
		while (canvas.horizontal < camera->canvas.horizontal)
		{
			win->world.ray = ray_for_pixel(camera, canvas);
			colour = colour_at(&win->world);
			img_pixel_put(win, canvas.horizontal, canvas.vertical,
				clamped_rgb_to_hex(&colour.tuple.colour));
			canvas.horizontal++;
		}
		canvas.vertical++;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
}
