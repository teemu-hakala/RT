#include "RTv1.h"

static t_tuple	default_origin(void)
{
	return (point(0, 0, 0));
}

static t_canvas	default_canvas(void)
{
	return ((t_canvas){.vertical = HEIGHT, .horizontal = WIDTH});
}

static t_transform	default_transform_1(void)
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

	d.translation = point(0, 0, 0);
	d.rotation = point(0, 0, 0);
	d.scale = point(0.5, 0.5, 0.5);
	transform_object(&d);
	return (d);
}

t_material	default_material_1(void)
{
	return ((t_material){
		.ambient = 0.1,
		.diffuse = 0.7,
		.specular = 0.2,
		.shininess = 200,
		.colour = colour(1.0, 0.8, 1.0, 0.6),
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
		.colour = colour(1.0, 0.8, 1.0, 0.6),
		.col_mash = vector(0, 0, 0),
		.amb_col = vector(0, 0, 0),
		.dif_col = vector(0, 0, 0),
		.spec_col = vector(0, 0, 0)
	});
}

static t_light	default_light(void)
{
	return ((t_light){
		.position = point(-10, 10, -10),
		.intensity = colour(1, 1, 1, 1),
		.transform = default_transform_1(),
	});
}

void	default_world(t_world *world)
{
	t_object	sphere_1;
	t_object	sphere_2;
	t_light		light;

	light = default_light();
	world->camera = camera(default_canvas(), M_PI_2);
	sphere_1 = sphere(default_origin(), default_transform_1(),
			default_material_1());
	sphere_2 = sphere(default_origin(), default_transform_2(),
			default_material_1());
	if (vec_push(&world->objects, &sphere_1) == VEC_ERROR)
		handle_errors("unable to malloc for world object");
	if (vec_push(&world->objects, &sphere_2) == VEC_ERROR)
		handle_errors("unable to malloc for world object");
	if (vec_push(&world->lights, &light) == VEC_ERROR)
		handle_errors("unable to malloc for light");
}
