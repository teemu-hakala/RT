











#include "RT.h"

void	shade_plane(t_world *world, void *plane, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;
	t_tuple	surface_col;
	t_tuple	reflected_col;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material = ((t_plane *)plane)->material
	};
	surface_col = lighting(&lighting_info, light, \
		world->hit.computations.vectors,world->hit.computations.over_point);
	reflected_col = reflected_colour(world, &world->hit.computations);
	*colour = tuple_add(tuple_add(surface_col, reflected_col), *colour);
}

void	shade_sphere(t_world *world, void *sphere, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;
	t_tuple	surface_col;
	t_tuple	reflected_col;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material = ((t_sphere *)sphere)->material
	};
	surface_col = lighting(&lighting_info, light, \
		world->hit.computations.vectors,world->hit.computations.over_point);
	reflected_col = reflected_colour(world, &world->hit.computations);
	*colour = tuple_add(tuple_add(surface_col, reflected_col), *colour);
}

void	shade_cone(t_world *world, void *cone, t_tuple *colour, t_light *light)
{
	t_info	lighting_info;
	t_tuple	surface_col;
	t_tuple	reflected_col;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material = ((t_cone *)cone)->material
	};
	surface_col = lighting(&lighting_info, light, \
		world->hit.computations.vectors,world->hit.computations.over_point);
	reflected_col = reflected_colour(world, &world->hit.computations);
	*colour = tuple_add(tuple_add(surface_col, reflected_col), *colour);
}

void	shade_cylinder(t_world *world, void *cylinder, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;
	t_tuple	surface_col;
	t_tuple	reflected_col;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material = ((t_cylinder *)cylinder)->material
	};
	surface_col = lighting(&lighting_info, light, \
		world->hit.computations.vectors,world->hit.computations.over_point);
	reflected_col = reflected_colour(world, &world->hit.computations);
	*colour = tuple_add(tuple_add(surface_col, reflected_col), *colour);
}

void	shade_cube(t_world *world, void *cube, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;
	t_tuple	surface_col;
	t_tuple	reflected_col;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material = ((t_cube *)cube)->material
	};
	surface_col = lighting(&lighting_info, light, \
		world->hit.computations.vectors,world->hit.computations.over_point);
	reflected_col = reflected_colour(world, &world->hit.computations);
	*colour = tuple_add(tuple_add(surface_col, reflected_col), *colour);
}
