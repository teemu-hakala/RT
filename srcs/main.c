










#include <stdio.h>
#include "RT.h"

// static void	open_scene_into(t_win *win, const char *str)
// {
// 	win->fd = open(str, O_RDONLY);
// 	if (win->fd < 0)
// 		handle_errors("unable to open file");
// }

// int	close_success(void)
// {
// 	handle_errors("All done :)");
// 	return (0);
// }

// int	main(int argc, char **argv)
// {
// 	t_win	win;

// 	if (argc != 2)
// 		handle_errors(USAGE);
// 	open_scene_into(&win, argv[1]);
// 	initialise_world(&win.world);
// 	parse_into(&win.world, win.fd);
// 	initialise_window(&win);
// 	render(&win, &win.world.camera);
// 	mlx_hook(win.win, KEY_DOWN, 0, handle_input, &win);
// 	mlx_hook(win.win, MOUSE_ESC, 0, close_success, &win);
// 	mlx_loop(win.mlx);
// 	return (0);
// }

t_object	cube(t_tuple origin, t_transform transform, t_material material)
{
	return ((t_object)
		{
			.object.cube = (t_cube)
			{
				.origin = origin,
				.transform = transform,
				.material = material
			},
			.type = OBJECT_CUBE
		}
	);
}

void	default_world(t_world *world)
{
	t_object	cube_1;
	t_light		light;

	cube_1 = cube(default_origin(), \
		default_transform_1(), default_phong_mat());
	if (vec_push(&world->objects, &cube_1) == VEC_ERROR)
		handle_errors("unable to malloc for world object");
	light = light_prototype();
	if (vec_push(&world->lights, &light) == VEC_ERROR)
		handle_errors("unable to malloc for light");
}

int	main(void)
{
	t_object	cube_1;
	t_tuple		p1;
	t_tuple		p2;
	t_tuple		p3;
	t_tuple		p4;

	t_tuple		vec;

	cube_1 = cube(default_origin(), default_transform_1(), default_phong_mat());
	p1 = point(1, 0.5, -0.8);
	p2 = point(-1, -0.2, 0.9);
	p3 = point(-0.4, 1, -0.1);
	p4 = point(0.3, -1, -0.7);
	vec = normal_at_cube(&cube_1, &p1);
	printf("(%0.2f, %0.2f, %0.2f)\n", vec.tuple.units.x, vec.tuple.units.y, \
		vec.tuple.units.z);
	vec = normal_at_cube(&cube_1, &p2);
	printf("(%0.2f, %0.2f, %0.2f)\n", vec.tuple.units.x, vec.tuple.units.y, \
		vec.tuple.units.z);
	vec = normal_at_cube(&cube_1, &p3);
	printf("(%0.2f, %0.2f, %0.2f)\n", vec.tuple.units.x, vec.tuple.units.y, \
		vec.tuple.units.z);
	vec = normal_at_cube(&cube_1, &p4);
	printf("(%0.2f, %0.2f, %0.2f)\n", vec.tuple.units.x, vec.tuple.units.y, \
		vec.tuple.units.z);
}
