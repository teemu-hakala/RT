
#include "RT.h"

void	shade_plane(t_world *world, void *plane, t_tuple *colour,
	t_light *light)
{
	t_info	light_info;
	t_tuple	temp_colour;

	is_shadow(world, world->hit.computations.over_point, light);
	light_info = get_lighting_info(((t_plane *)plane)->material, \
		((t_plane *)plane)->appearance, ((t_plane *)plane)->transform, \
			((t_plane *)plane)->material.init_colour);
	//world->hit.computations.reflective = light_info.material.reflectiveness;
	temp_colour = lighting(&light_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	if (light_info.appearance.pattern.type > 0 || \
		light_info.appearance.texture.type > 0)
	{
		light_info.col = get_appearance_colour(&light_info, \
			&world->hit.computations.over_point, planar_map);
		temp_colour = lighting(&light_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	}
	*colour = tuple_add(*colour, temp_colour);
	*colour = tuple_add(*colour, \
		reflected_colour(world, &world->hit.computations));
}

void	shade_sphere(t_world *world, void *sphere, t_tuple *colour,
	t_light *light)
{
	t_info	light_info;
	t_tuple	temp_colour;

	is_shadow(world, world->hit.computations.over_point, light);
	light_info = get_lighting_info(((t_sphere *)sphere)->material, \
		((t_sphere *)sphere)->appearance, ((t_sphere *)sphere)->transform, \
			((t_sphere *)sphere)->material.init_colour);
	//world->hit.computations.reflective = light_info.material.reflectiveness;
	temp_colour = lighting(&light_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	if (light_info.appearance.pattern.type > 0 || \
		light_info.appearance.texture.type > 0)
	{
		light_info.col = get_appearance_colour(&light_info, \
			&world->hit.computations.over_point, spherical_map);
		temp_colour = lighting(&light_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	}
	*colour = tuple_add(*colour, temp_colour);
	*colour = tuple_add(*colour, \
		reflected_colour(world, &world->hit.computations));
}

void	shade_cone(t_world *world, void *cone, t_tuple *colour, t_light *light)
{
	t_info	light_info;
	t_tuple	temp_colour;

	is_shadow(world, world->hit.computations.over_point, light);
	light_info = get_lighting_info(((t_cone *)cone)->material, \
		((t_cone *)cone)->appearance, ((t_cone *)cone)->transform, \
			((t_cone *)cone)->material.init_colour);
	//world->hit.computations.reflective = light_info.material.reflectiveness;
	temp_colour = lighting(&light_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	if (light_info.appearance.pattern.type > 0 || \
		light_info.appearance.texture.type > 0)
	{
		light_info.col = get_appearance_colour(&light_info, \
			&world->hit.computations.over_point, conical_map);
		temp_colour = lighting(&light_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	}
	*colour = tuple_add(*colour, temp_colour);
	*colour = tuple_add(*colour, \
		reflected_colour(world, &world->hit.computations));
}

void	shade_cylinder(t_world *world, void *cylinder, t_tuple *colour,
	t_light *light)
{
	t_info	light_info;
	t_tuple	temp_colour;

	is_shadow(world, world->hit.computations.over_point, light);
	light_info = get_lighting_info(((t_cylinder *)cylinder)->material, \
		((t_cylinder *)cylinder)->appearance, \
		((t_cylinder *)cylinder)->transform, \
		((t_cylinder *)cylinder)->material.init_colour);
	//world->hit.computations.reflective = light_info.material.reflectiveness;
	temp_colour = lighting(&light_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	if (light_info.appearance.pattern.type > 0 || \
		light_info.appearance.texture.type > 0)
	{
		light_info.col = get_appearance_colour(&light_info, \
			&world->hit.computations.over_point, cylindrical_map);
		temp_colour = lighting(&light_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	}
	*colour = tuple_add(*colour, temp_colour);
	*colour = tuple_add(*colour, \
		reflected_colour(world, &world->hit.computations));
}

void	shade_cube(t_world *world, void *cube, t_tuple *colour,
	t_light *light)
{
	t_info	light_info;
	t_tuple	temp_colour;

	is_shadow(world, world->hit.computations.over_point, light);
	light_info = get_lighting_info(((t_cube *)cube)->material, \
		((t_cube *)cube)->appearance, ((t_cube *)cube)->transform, \
			((t_cube *)cube)->material.init_colour);
	//world->hit.computations.reflective = light_info.material.reflectiveness;
	temp_colour = lighting(&light_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	if (light_info.appearance.pattern.type > 0 || \
		light_info.appearance.texture.type > 0)
	{
		light_info.col = get_appearance_colour(&light_info, \
			&world->hit.computations.over_point, cubic_map);
		temp_colour = lighting(&light_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	}
	*colour = tuple_add(*colour, temp_colour);
	*colour = tuple_add(*colour, \
		reflected_colour(world, &world->hit.computations));
}
