











#include "RT.h"

void	shade_plane(t_world *world, void *plane, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;
	t_tuple temp;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material = ((t_plane *)plane)->material
	};
	temp = transform_point(&world->hit.computations.over_point, \
		&((t_plane *)plane)->transform, &((t_plane *)plane)->pattern.transform);
	((t_plane *)plane)->pattern.map = planar_map(&temp);
	pattern_at(&((t_plane *)plane)->pattern, &((t_plane *)plane)->material, \
		&((t_plane *)plane)->pattern.map);
	*colour = tuple_add(lighting(&lighting_info, \
		light, world->hit.computations.vectors, \
		world->hit.computations.over_point), *colour);
}

void	shade_sphere(t_world *world, void *sphere, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;
	t_tuple temp;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material = ((t_sphere *)sphere)->material
	};
	temp = transform_point(&world->hit.computations.over_point, \
		&((t_sphere *)sphere)->transform, &((t_sphere *)sphere)->pattern.transform);
	((t_sphere *)sphere)->pattern.map = spherical_map(&temp);
	pattern_at(&((t_sphere *)sphere)->pattern, &((t_sphere *)sphere)->material, \
	&((t_sphere *)sphere)->pattern.map);
	*colour = tuple_add(lighting(&lighting_info, \
		light, world->hit.computations.vectors, \
		world->hit.computations.over_point), *colour);
}

void	shade_cone(t_world *world, void *cone, t_tuple *colour, t_light *light)
{
	t_info	lighting_info;
	t_tuple temp;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material = ((t_cone *)cone)->material
	};
	temp = transform_point(&world->hit.computations.over_point, \
		&((t_cone *)cone)->transform, &((t_cone *)cone)->pattern.transform);
	((t_cone *)cone)->pattern.map = conical_map(&temp);
	pattern_at(&((t_cone *)cone)->pattern, &((t_cone *)cone)->material, \
		&((t_cone *)cone)->pattern.map);
	*colour = tuple_add(lighting(&lighting_info, \
		light, world->hit.computations.vectors, \
		world->hit.computations.over_point), *colour);
}

void	shade_cylinder(t_world *world, void *cylinder, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;
	t_tuple temp;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material = ((t_cylinder *)cylinder)->material
	};
	temp = transform_point(&world->hit.computations.over_point, \
		&((t_cylinder *)cylinder)->transform, &((t_cylinder *)cylinder)->pattern.transform);
	((t_cylinder *)cylinder)->pattern.map = cylindrical_map(&temp);
	pattern_at(&((t_cylinder *)cylinder)->pattern,
		&((t_cylinder *)cylinder)->material,
		&((t_cylinder *)cylinder)->pattern.map);
	*colour = tuple_add(lighting(&lighting_info, \
		light, world->hit.computations.vectors, \
		world->hit.computations.over_point), *colour);
}

void	shade_cube(t_world *world, void *cube, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;
	t_tuple	temp;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info = (t_info){
		.material = ((t_cube *)cube)->material
	};
	temp = transform_point(&world->hit.computations.over_point, \
		&((t_cube *)cube)->transform, &((t_cube *)cube)->pattern.transform);
	((t_cube *)cube)->pattern.map = cubic_map(&temp, &((t_cube *)cube)->pattern);
	pattern_at(&((t_cube *)cube)->pattern,
		&((t_cube *)cube)->material,
		&((t_cube *)cube)->pattern.map);
	*colour = tuple_add(lighting(&lighting_info, \
		light, world->hit.computations.vectors, \
		world->hit.computations.over_point), *colour);
}
