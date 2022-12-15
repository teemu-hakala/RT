











#include "RT.h"

void	shade_plane(t_world *world, void *plane, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material = ((t_plane *)plane)->material
	};
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
	*colour = tuple_add(lighting(&lighting_info, \
		light, world->hit.computations.vectors, \
		world->hit.computations.over_point), *colour);
}

void	shade_cube(t_world *world, void *cube, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material = ((t_cube *)cube)->material
	};
	*colour = tuple_add(lighting(&lighting_info, \
		light, world->hit.computations.vectors, \
		world->hit.computations.over_point), *colour);
}
