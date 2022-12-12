











#include "RT.h"

void	shade_plane(t_world *world, void *plane, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material =	((t_plane *)plane)->material
	};
	*colour = tuple_add(lighting(&lighting_info, \
		light, world->hit.computations.vectors, \
		world->hit.computations.over_point), *colour);
	*colour = tuple_add(reflected_colour(

		), *colour);
}

void	shade_sphere(t_world *world, void *sphere, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material =	((t_sphere *)sphere)->material
	};
	*colour = tuple_add(lighting(&lighting_info, \
		light, world->hit.computations.vectors, \
		world->hit.computations.over_point), *colour);
	*colour = tuple_add(reflected_colour(

		), *colour);
}

void	shade_cone(t_world *world, void *cone, t_tuple *colour, t_light *light)
{
	t_info	lighting_info;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material =	((t_cone *)cone)->material
	};
	*colour = tuple_add(lighting(&lighting_info, \
		light, world->hit.computations.vectors, \
		world->hit.computations.over_point), *colour);
	*colour = tuple_add(reflected_colour(

		), *colour);
}

void	shade_cylinder(t_world *world, void *cylinder, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material =	((t_cylinder *)cylinder)->material
	};
	*colour = tuple_add(lighting(&lighting_info, \
		light, world->hit.computations.vectors, \
		world->hit.computations.over_point), *colour);
	*colour = tuple_add(reflected_colour(

		), *colour);
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
		shape_shading[world->hit.intersection.shape->type \
			- OBJECT_INDEX_OFFSET] \
			(world, &world->hit.intersection.shape->object, &colour, light);
		i++;
	}
	return (colour);
}
