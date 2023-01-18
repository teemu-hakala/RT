










#include "RT.h"

void	initialise_image(t_img *img, t_win *win)
{
	t_canvas	dimensions;

	dimensions = (t_canvas){.horizontal = WIDTH, .vertical = HEIGHT};
	img->dimensions = (t_rectangle){.canvas = dimensions, \
		.start = {0, 0}, .end = dimensions};
	img->img = mlx_new_image(win->mlx, dimensions.horizontal, \
		dimensions.vertical);
	if (!img->img)
		handle_errors("error");
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->length, \
		&img->endian);
	if (!img->addr)
		handle_errors("img->addr is NULL");
}

void	initialise_world(t_world *world)
{
	world->camera = camera_prototype();
	if (vec_new(&world->lights, 1, sizeof(t_light)) != VEC_SUCCESS
		|| vec_new(&world->objects, 1, sizeof(t_object)) != VEC_SUCCESS
		|| vec_new(&world->intersections, 1, sizeof(t_intersect))
		!= VEC_SUCCESS)
		handle_errors("initialise_world malloc returned NULL");
	world->hit.hit_check = false;
	world->lifetime = 5;
	world->filter = GRAYSCALE;
}

void	initialise_window(t_win *win)
{
	win->mlx = mlx_init();
	if (!win->mlx)
		handle_errors("error");
	win->win = mlx_new_window(win->mlx, win->world.camera.canvas.horizontal, \
		win->world.camera.canvas.vertical, "RTV1");
	if (!win->win)
		handle_errors("error");
	initialise_image(&win->img, win);
	win->progress = NULL;
	win->drawn = false;
	pthread_mutex_init(&win->drawn_mutex, NULL);
	win->input.mouse.rmb_is_down = false;
	win->pixels = (WIDTH * HEIGHT) / THREAD_COUNT;
	win->remaining_pixels = (WIDTH * HEIGHT - THREAD_COUNT * win->pixels);
	win->rotation_step = M_PI / 448;
	win->input.mouse.mode = MODE_NONE;
	win->keys_image = (t_img){};
	win->keys_visible = false;
	win->input.mouse.compounder = (t_compounder){};
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
