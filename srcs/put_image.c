










#include <stdio.h>
#include "RT.h"

int	put_image(t_win *win)
{
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
	return (0);
}
