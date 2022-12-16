











#include "RT.h"
#include <stdio.h>

void	prepare_object(t_world *world, t_object *object, t_comp *computations);
t_ray	ray(t_tuple origin, t_tuple reflectv, int64_t lt);

static void	precomputing_reflection_vector(void)
{
	t_world		world_prototype;
	t_object	plane_object;
	t_ray		ray_for_reflection;

	plane_object = plane_prototype();
	ray_for_reflection = ray(point(0, 1, -1), vector(0, -0.7071, 0.7071), 5);
	world_prototype = (t_world){
		.hit = {.intersection = {.shape = &plane_object, .time = 1}},
		.ray = ray_for_reflection
	};
	prepare_computations(&world_prototype);
	printf("%0.2f, %0.2f, %0.2f\n", world_prototype.hit.computations.reflectv.tuple.units.x,\
	world_prototype.hit.computations.reflectv.tuple.units.y, world_prototype.hit.computations.reflectv.tuple.units.z);
}

void	reflection_tests(void)
{
	precomputing_reflection_vector();
}

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
	mlx_hook(win.win, MOUSE_ESC, 0, close_success, &win);
	mlx_loop(win.mlx);
	return (0);
}

// int main(void)
// {
// 	reflection_tests();
// 	return (0);
// }
