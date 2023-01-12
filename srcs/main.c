#include "RT.h"

static void	open_scene_into(t_win *win, const char *str)
{
	win->fd = open(str, O_RDONLY);
	if (win->fd < 0)
		handle_errors("unable to open file");
}

int	close_success(void)
{
	handle_errors("All done :)");
	return (0);
}

int	expose_handler(t_win *win)
{
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
	return (0);
}

void	hooks(t_win *win)
{
	mlx_hook(win->win, KEY_DOWN, 0, handle_input, win);
	mlx_hook(win->win, MOUSE_ESC, 0, close_success, win);
	mlx_hook(win->win, ON_MOUSE_DOWN, 0, mouse_handler_down, win);
	mlx_hook(win->win, ON_MOUSE_MOVE, 0, mouse_handler_move, win);
	mlx_hook(win->win, ON_MOUSE_UP, 0, mouse_handler_up, win);
	mlx_expose_hook(win->win, expose_handler, win);
}

int	main(int argc, char **argv)
{
	t_win	win;

	if (argc != 2)
		handle_errors(USAGE);
	open_scene_into(&win, argv[1]);
	initialise_world(&win.world);
	parse_into(&win.world, win.fd);
	initialise_window(&win);
	render(&win, &win.world.camera);
	hooks(&win);
	mlx_loop(win.mlx);
	return (0);
}
