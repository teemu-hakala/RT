











#include "RT.h"


int midasdsaasddsaadsasd;

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
			if (canvas.horizontal == 225 && canvas.vertical == 246)
				midasdsaasddsaadsasd = 1;
			else
				midasdsaasddsaadsasd = 0;
			win->world.ray = ray_for_pixel(camera, canvas);
			win->world.lifetime = 1;
			colour = colour_at(&win->world, win->world.ray);
			img_pixel_put(win, canvas.horizontal, canvas.vertical,
				clamped_rgb_to_hex(&colour.tuple.colour));
			canvas.horizontal++;
		}
		canvas.vertical++;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
}
