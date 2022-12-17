











#include "RT.h"
#include <stdio.h>

void		prepare_object(t_world *world, t_object *object, t_comp *computations);
t_ray		ray(t_tuple origin, t_tuple reflectv, int64_t lt);
t_transform	default_transform_1(void);

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

static void	nonreflective_material(void)
{
	t_world		default_world;
	t_object	sphere;
	t_info		lighting_info;
	t_tuple		colour;


	default_world.camera = camera_prototype();
	if (vec_new(&default_world.lights, 1, sizeof(t_light)) != VEC_SUCCESS
		|| vec_new(&default_world.objects, 1, sizeof(t_object)) != VEC_SUCCESS
		|| vec_new(&default_world.intersections, 1, sizeof(t_intersect))
		!= VEC_SUCCESS)
		handle_errors("initialise_default_world malloc returned NULL");
	default_world.hit.hit_check = false;
	sphere = (t_object){
		.object = {
			.sphere = {
				.origin = {.tuple.units = {0, 0, 0, 0}},
				.transform = default_transform_1(),
				.material = default_material_1()
			}
		},
		.type = OBJECT_SPHERE
	};
	sphere.object.sphere.material.reflectiveness = 1;
	vec_push(&default_world.objects, &sphere);
	sphere.object.sphere.transform.scale = point(0.5, 0.5, 0.5);
	sphere.object.sphere.material.ambient = 1;
	sphere.object.sphere.material.reflectiveness = 0;
	vec_push(&default_world.objects, &sphere);
	default_world.hit.intersection = (t_intersect){
		.shape = vec_get(&default_world.objects, 1),
		.time = 1
	};
	default_world.ray = ray(point(0, 0, 0), vector(0, 0, 1), 5);
	prepare_object(&default_world, default_world.hit.intersection.shape, &default_world.hit.computations);
	lighting_info = (t_info){
		.material =	default_world.hit.intersection.shape->object.sphere.material
	};
	colour = reflected_colour(&default_world, &lighting_info);
	(void)colour;
}

void	reflection_tests(void)
{
	precomputing_reflection_vector();
	nonreflective_material();
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

	reflection_tests();
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
