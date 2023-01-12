











#include "RT.h"

t_img	progress_bar_image(t_win *win, t_canvas *bar_dimensions, uint8_t flag)
{
	static t_img		bar_img = {};
	static t_rectangle	filler;

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
		filler = (t_rectangle){{}, *bar_dimensions, {}};
	}
	if (flag & BAR_CLEAR || bar_img.img == NULL)
		put_rectangle_to_image(bar_img, filler, filler, \
			(t_tuple){.tuple.colour = {0, 0, 0, 1}});
	return (bar_img);
}
