










#include <stdio.h>
#include "RT.h"

int	put_image(t_win *win)
{
	static int	first = 1;

	if (first)
	{
		// threaded_loop_mid(win);
		threaded_loop(win);
		first = 0;
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
	return (0);
}
