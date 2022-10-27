#include "RTv1.h"

/*void	background_colour(t_win *win)
{
	int		x;
	int		y;
	// t_tuple	colour;

	// colour = hex_to_argb(COLOUR_TURQOUISE);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			img_pixel_put(win, x, y, COLOUR_TURQOUISE);
		}
	}
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
}*/

void	initialise_image(t_img *img, t_win *win)
{
	img->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	if (!img->img)
		handle_errors("error");
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->length, \
		&img->endian);
	if (!img->addr)
		handle_errors("img->addr is NULL");
}

void	initialise_world(t_world *world)
{
	if (vec_new(&world->lights, 1, sizeof(t_light)) != VEC_SUCCESS
		|| vec_new(&world->objects, 1, sizeof(t_object)) != VEC_SUCCESS
		|| vec_new(&world->intersections, 1, sizeof(t_intersect))
		!= VEC_SUCCESS)
		handle_errors("initialise_world malloc returned NULL");
	world->hit.intersection = NULL;
	default_world(world);
}

void	initialise_window(t_win *win)
{
	win->mlx = mlx_init();
	if (!win->mlx)
		handle_errors("error");
	win->win = mlx_new_window(win->mlx, WIDTH, HEIGHT, "RTV1");
	if (!win->win)
		handle_errors("error");
	initialise_image(&win->img, win);
	// background_colour(win);
}

void	identity_matrix_set(t_mtx *dst)
{
	dst->tuple_rows[0] = (t_quad_tuple){1.0, 0.0, 0.0, 0.0};
	dst->tuple_rows[1] = (t_quad_tuple){0.0, 1.0, 0.0, 0.0};
	dst->tuple_rows[2] = (t_quad_tuple){0.0, 0.0, 1.0, 0.0};
	dst->tuple_rows[3] = (t_quad_tuple){0.0, 0.0, 0.0, 1.0};
}

t_mtx	identity_matrix(void)
{
	return ((t_mtx){
		.tuple_rows = {
			(t_quad_tuple){1.0, 0.0, 0.0, 0.0}, \
			(t_quad_tuple){0.0, 1.0, 0.0, 0.0}, \
			(t_quad_tuple){0.0, 0.0, 1.0, 0.0}, \
			(t_quad_tuple){0.0, 0.0, 0.0, 1.0}
		}
		});
}
