










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
	t_world		world;
	t_ray		ray;
	uint16_t	i;


	i = 0;
	initialise_world(&world);
	printf("%llu objects in world\n", world.objects.len);
	while (i < world.objects.len)
	{
		printf("object: %d\n", ((t_object *)vec_get(&world.objects, i))->type);
		i++;
	}
	ray.origin.tuple.units = (t_units){0, 0.5, 0, POINT_1};
	ray.direction.tuple.units = (t_units){0, 0, 1, VECTOR_0};
	ray.direction = normalize(ray.direction);
	vec_clear(&world.intersections);
	intersect_world(&world, ray);
	printf("%llu intersections found\n", world.intersections.len);
	identify_hit(&world, &world.hit);
	if (world.hit.hit_check == true)
		printf("no hits\n");
	else
		printf("hit time: %f\n", world.hit.intersection.time);

}
