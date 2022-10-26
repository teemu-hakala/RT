#include "RTv1.h"

static t_tuple	default_origin(void)
{
	return (point(0, 0, 0));
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

static t_transform	default_transform_2(void)
{
	t_transform	d;

	d.translation = point(0, 0, 0);
	d.rotation = point(0, 0, 0);
	d.scale = point(0.5, 0.5, 0.5);
	transform_object(&d);
	return (d);
}

static t_material	default_material_1(void)
{
	return ((t_material){
		.ambient = 0.1,
		.diffuse = 0.9,
		.specular = 0.9,
		.shininess = 200,
		.colour = (t_tuple)
		{
			.tuple.colour = {.a = 0.0, .r = 0.8, .g = 1.0, .b = 0.6}
		}
	});
}

static t_material	default_material_2(void)
{
	return ((t_material){
		.ambient = 0.1,
		.diffuse = 0.9,
		.specular = 0.9,
		.shininess = 200,
		.colour = (t_tuple)
		{
			.tuple.colour = {.a = 0.0, .r = 1.0, .g = 0.2, .b = 1.0}
		}
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
	sphere_1 = sphere(default_origin(), default_transform_1(),
			default_material_1());
	sphere_2 = sphere(default_origin(), default_transform_2(),
			default_material_2());
	if (vec_push(&world->objects, &sphere_1) == VEC_ERROR)
		handle_errors("unable to malloc for world object");
	if (vec_push(&world->objects, &sphere_2) == VEC_ERROR)
		handle_errors("unable to malloc for world object");
	if (vec_push(&world->lights, &light) == VEC_ERROR)
		handle_errors("unable to malloc for light");
}
