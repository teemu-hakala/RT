










#include "RT.h"

char	command_key_state(int change_state)
{
	static char	toggled_on = false;

	if (change_state)
		toggled_on = !toggled_on;
	return (toggled_on);
}

t_img	initialise_keys_image(void *mlx, t_canvas canvas)
{
	t_img		keys_image;

	keys_image.dimensions = (t_rectangle){.start = \
		{.vertical = canvas.vertical * 0.125, .horizontal = canvas.horizontal \
		* 0.125}, .end = {.vertical = canvas.vertical * 0.875, .horizontal = \
		canvas.horizontal = canvas.horizontal * 0.375}};
	keys_image.dimensions.canvas = (t_canvas){
		keys_image.dimensions.end.vertical - \
		keys_image.dimensions.start.vertical,
		keys_image.dimensions.end.horizontal - \
		keys_image.dimensions.start.horizontal \
	};
	keys_image.img = mlx_new_image(mlx, \
		keys_image.dimensions.canvas.horizontal, \
		keys_image.dimensions.canvas.vertical);
	if (keys_image.img == NULL)
		handle_errors("keys_image got NULL");
	keys_image.addr = mlx_get_data_addr(keys_image.img, &keys_image.bpp, \
		&keys_image.length, &keys_image.endian);
	if (keys_image.addr == NULL)
		handle_errors("keys_image got NULL");
	return (keys_image);
}

void	print_text_on_keys_image(t_win *win, t_img *keys_image)
{
	uint16_t	row;
	uint16_t	column;

	row = keys_image->dimensions.start.vertical;
	column = keys_image->dimensions.start.horizontal;
	mlx_string_put(win->mlx, win->win, column, row, 0x00FFFFFF, "hello world");
}

void	put_keys_image(t_win *win)
{
	if (win->keys_visible)
	{
		mlx_put_image_to_window(win->mlx, win->win, win->keys_image.img, \
			win->keys_image.dimensions.start.horizontal, \
			win->keys_image.dimensions.start.vertical);
		print_text_on_keys_image(win, &win->keys_image);
	}
	else
		mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
}

void	toggle_key_user_interface(t_win *win)
{
	if (win->keys_image.addr == NULL)
	{
		win->keys_image = initialise_keys_image(win->mlx, \
			win->world.camera.canvas);
		put_rectangle_to_image(win->keys_image,
			(t_rectangle){.start = {0, 0}, .end = {.vertical = \
			win->keys_image.dimensions.canvas.vertical, .horizontal = \
			win->keys_image.dimensions.canvas.horizontal}, .canvas = {}}, \
			win->keys_image.dimensions, \
			(t_tuple){.tuple.colour = {.r = 0, .g = 0, .b = 1, .a = 0}});
	}
	win->keys_visible = !win->keys_visible;
	put_keys_image(win);
}
