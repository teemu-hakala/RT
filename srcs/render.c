











#include "RT.h"

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
			win->world.lifetime = 3;
			colour = colour_at(&win->world, win->world.ray);
			img_pixel_put(win, canvas.horizontal, canvas.vertical,
				clamped_rgb_to_hex(&colour.tuple.colour));
			canvas.horizontal++;
		}
		canvas.vertical++;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
}
