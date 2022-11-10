#include "RTv1.h"

t_tuple	default_origin(void)
{
	return (point(0, 0, 0));
}

t_tuple	origin_1(void)
{
	return (point(0, 0, 0));
}

t_tuple	camera_origin(void)
{
	return (point(0, 0, -5));
}

t_canvas	default_canvas(void)
{
	return ((t_canvas){.vertical = HEIGHT, .horizontal = WIDTH});
}

t_transform	default_transform_1(void)
{
	t_transform	d;

	d.translation = point(0, 0, 0);
	d.rotation = point(0, 0, 0);
	d.scale = point(1, 1, 1);
	transform_object(&d);
	return (d);
}

t_transform	camera_transform(void)
{
	t_transform	d;

	d.translation = point(0, 0, 0);
	d.rotation = point(0, 0, 0);
	d.scale = point(1, 1, 1);
	transform_object(&d);
	return (d);
}

t_transform	default_transform_2(void)
{
	t_transform	d;

	d.translation = point(0, 0.8, 0);
	d.rotation = point(0, 0, 0);
	d.scale = point(0.5, 0.5, 0.5);
	transform_object(&d);
	return (d);
}

t_material	default_phong_mat(void)
{
	return ((t_material){
		.ambient = 0.1,
		.diffuse = 0.9,
		.specular = 0.9,
		.shininess = 200,
		.init_colour = colour(1.0, 1.0, 1.0, 1.0),
		.col_mash = vector(0, 0, 0),
		.amb_col = vector(0, 0, 0),
		.dif_col = vector(0, 0, 0),
		.spec_col = vector(0, 0, 0)
	});
}

t_material	default_material_1(void)
{
	return ((t_material){
		.ambient = 0.1,
		.diffuse = 0.7,
		.specular = 0.2,
		.shininess = 200,
		.init_colour = colour(1.0, 0.8, 1.0, 0.6),
		.col_mash = vector(0, 0, 0),
		.amb_col = vector(0, 0, 0),
		.dif_col = vector(0, 0, 0),
		.spec_col = vector(0, 0, 0)
	});
}

t_material	default_material_2(void)
{
	return ((t_material){
		.ambient = 0.1,
		.diffuse = 0.9,
		.specular = 0.9,
		.shininess = 200,
		.init_colour = colour(1.0, 0.8, 1.0, 0.6),
		.col_mash = vector(0, 0, 0),
		.amb_col = vector(0, 0, 0),
		.dif_col = vector(0, 0, 0),
		.spec_col = vector(0, 0, 0)
	});
}

void	default_world(t_world *world)
{
	t_object	sphere_1;
	t_object	sphere_2;
	t_object	cylinder_1;
	t_mtx		view_matrix;
	t_object	cone_1;
	t_light		light;

	sphere_1 = sphere(default_origin(), default_transform_1(),
			default_material_1());
	sphere_2 = sphere(origin_1(), default_transform_2(),
			default_material_1());
	cylinder_1 = cylinder(default_origin(), default_transform(),default_phong_mat());
	cone_1 = cone(default_origin(), default_transform(), default_phong_mat());
	world->camera = camera(camera_origin(), camera_transform(), M_PI_2, default_canvas());
	view_matrix = view_transform(world->camera.origin, point(0, 0, 0), vector(0, 1, 0));
	matrix_multi_square(&world->camera.transform.matrix, &view_matrix, 4);
	world->camera.transform.inverse = world->camera.transform.matrix;
	matrix_inversion(&world->camera.transform.inverse, 4);
	if (vec_push(&world->objects, &sphere_1) == VEC_ERROR)
		handle_errors("unable to malloc for world object");
	if (vec_push(&world->objects, &sphere_2) == VEC_ERROR)
		handle_errors("unable to malloc for world object");
	if (vec_push(&world->objects, &cylinder_1) == VEC_ERROR)
		handle_errors("unable to malloc for world object");
	if (vec_push(&world->objects, &cone_1) == VEC_ERROR)
		handle_errors("unable to malloc for world object");
	light = default_light();
	if (vec_push(&world->lights, &light) == VEC_ERROR)
		handle_errors("unable to malloc for light");
}

void	simple_world(t_world *world)
{
	t_object	sphere_1;
	t_object	floor;
	t_mtx		view_matrix;
	t_light		light;

	sphere_1 = sphere(default_origin(), default_transform_1(),
			default_material_1());
	floor = plane(plane_origin(), plane_transform_floor(), plane_material_floor());
	light = default_light();
	world->camera = camera(camera_origin(), camera_transform(), M_PI_2, default_canvas());
	view_matrix = view_transform(world->camera.origin, point(0, 0, 0), vector(0, 1, 0));
	matrix_multi_square(&world->camera.transform.matrix, &view_matrix, 4);
	world->camera.transform.inverse = world->camera.transform.matrix;
	matrix_inversion(&world->camera.transform.inverse, 4);
	if (vec_push(&world->objects, &sphere_1) == VEC_ERROR)
		handle_errors("unable to malloc for world object");
	if (vec_push(&world->objects, &floor) == VEC_ERROR)
		handle_errors("unable to malloc for world object");
	if (vec_push(&world->lights, &light) == VEC_ERROR)
		handle_errors("unable to malloc for light");
	light.position = point(0, 10, 2);
	if (vec_push(&world->lights, &light) == VEC_ERROR)
		handle_errors("unable to malloc for light");
}
