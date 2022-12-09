











#include "RT.h"

void	shade_plane(t_world *world, void *plane, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material = ((t_plane *)plane)->material
	};
	pattern_at(&((t_plane *)plane)->pattern, &((t_plane *)plane)->material, \
		&world->hit.computations.over_point, ((t_plane *)plane)->transform);
	*colour = tuple_add(lighting(&lighting_info, \
		light, world->hit.computations.vectors, \
		world->hit.computations.over_point), *colour);
}

void	shade_sphere(t_world *world, void *sphere, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material = ((t_sphere *)sphere)->material
	};
	pattern_at(&((t_sphere *)sphere)->pattern, &((t_sphere *)sphere)->material, \
		&world->hit.computations.over_point, ((t_sphere *)sphere)->transform);
	*colour = tuple_add(lighting(&lighting_info, \
		light, world->hit.computations.vectors, \
		world->hit.computations.over_point), *colour);
}

void	shade_cone(t_world *world, void *cone, t_tuple *colour, t_light *light)
{
	t_info	lighting_info;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material = ((t_cone *)cone)->material
	};
	pattern_at(&((t_cone *)cone)->pattern, &((t_cone *)cone)->material, \
		&world->hit.computations.over_point, ((t_cone *)cone)->transform);
	*colour = tuple_add(lighting(&lighting_info, \
		light, world->hit.computations.vectors, \
		world->hit.computations.over_point), *colour);
}

void	shade_cylinder(t_world *world, void *cylinder, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material = ((t_cylinder *)cylinder)->material
	};
	pattern_at(&((t_cylinder *)cylinder)->pattern,
		&((t_cylinder *)cylinder)->material,
		&world->hit.computations.over_point,
		((t_cylinder *)cylinder)->transform);
	*colour = tuple_add(lighting(&lighting_info, \
		light, world->hit.computations.vectors, \
		world->hit.computations.over_point), *colour);
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
