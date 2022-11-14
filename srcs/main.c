#include "../includes/RTv1.h"

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
	mlx_hook(win.win, KEY_DOWN, 0, handle_input, &win);
	mlx_loop(win.mlx);
	return (0);
}
