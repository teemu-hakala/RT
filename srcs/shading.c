#include "RTv1.h"

void	shade_plane(t_world *world, void *plane, t_tuple *colour, t_light *light)
{
	*colour = tuple_add((lighting(((t_plane *)plane)->material, \
		light, world->hit.computations.vectors, \
		world->hit.computations.point)), *colour);
}

void	shade_sphere(t_world *world, void *sphere, t_tuple *colour, t_light *light)
{

	*colour = tuple_add((lighting(((t_sphere *)sphere)->material, \
		light, world->hit.computations.vectors, \
		world->hit.computations.point)), *colour);
}

void	shade_cone(t_world *world, void *cone, t_tuple *colour, t_light *light)
{

	*colour = tuple_add((lighting(((t_cone *)cone)->material, \
		light, world->hit.computations.vectors, \
		world->hit.computations.point)), *colour);
}

void	shade_cylinder(t_world *world, void *cylinder, t_tuple *colour, t_light *light)
{
	*colour = tuple_add((lighting(((t_cylinder *)cylinder)->material, \
		light, world->hit.computations.vectors, \
		world->hit.computations.point)), *colour);
}

t_tuple	shade_hit(t_world *world)
{
	static const t_shading_function	\
				shape_shading[] = {
		shade_plane,
		shade_sphere,
		shade_cone,
		shade_cylinder
	};
	t_tuple		colour;
	t_light		*light;
	uint64_t	i;


	colour.tuple.colour = (t_colour){0.0, 0.0, 0.0, 0.0};
	i = 0;
	while (i < world->lights.len)
	{
		light = (t_light *)vec_get(&world->lights, i);
		shape_shading[world->hit.intersection->shape->type \
			- OBJECT_INDEX_OFFSET] \
			(world, &world->hit.intersection->shape->object, &colour, light);
		i++;
	}
	// printf("colour: a: %f, r: %f, g: %f, b:%f\n", colour.tuple.colour.a, \
	// 	colour.tuple.colour.r, colour.tuple.colour.g, colour.tuple.colour.b);
	return (colour);
}



