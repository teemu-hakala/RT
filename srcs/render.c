#include "RTv1.h"

void	render(t_win *win, t_camera *camera)
{
	t_canvas	canvas;
	t_tuple		colour;
	t_ray		ray;

	canvas.vertical = 0;
	while (canvas.vertical < camera->size.vertical)
	{
		canvas.horizontal = 0;
		while (canvas.horizontal < camera->size.horizontal)
		{
			win->world.ray = ray_for_pixel(*camera, (t_canvas){.vertical = \
				canvas.vertical, .horizontal = canvas.horizontal});
			colour = colour_at(&win->world);
			img_pixel_put(win->win, canvas.horizontal, canvas.vertical,
				argb_to_hex(&colour.tuple.colour));
			canvas.horizontal++;
		}
		canvas.vertical++;
	}
}
