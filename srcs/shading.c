











// #include "RT.h"

// void	shade_plane(t_world *world, void *plane, t_tuple *colour,
// 	t_light *light)
// {
// 	t_info	lighting_info;
// 	t_tuple	temp;

// 	is_shadow(world, world->hit.computations.over_point, light);
// 	lighting_info = (t_info){
// 		.material = ((t_plane *)plane)->material
// 	};
// 	pattern_at(&((t_plane *)plane)->appearance.pattern, \
// 		&((t_plane *)plane)->material, ((t_plane *)plane)->transform, \
// 		&world->hit.computations.over_point);
// 	temp = transform_point(&world->hit.computations.over_point, \
// 		&((t_plane *)plane)->transform, \
// 			&((t_plane *)plane)->appearance.texture.transform);
// 	((t_plane *)plane)->appearance.texture.map = planar_map(&temp);
// 	texture_at(&((t_plane *)plane)->appearance.texture, \
// 		&((t_plane *)plane)->material, \
// 		&((t_plane *)plane)->appearance.texture.map);
// 	*colour = tuple_add(lighting(&lighting_info, \
// 		light, world->hit.computations.vectors, \
// 		world->hit.computations.over_point), *colour);
// }

// void	shade_sphere(t_world *world, void *sphere, t_tuple *colour,
// 	t_light *light)
// {
// 	t_info	lighting_info;
// 	t_tuple	temp;

// 	is_shadow(world, world->hit.computations.over_point, light);
// 	lighting_info = (t_info){
// 		.material = ((t_sphere *)sphere)->material
// 	};
// 	pattern_at(&((t_sphere *)sphere)->appearance.pattern, \
// 		&((t_sphere *)sphere)->material, ((t_sphere *)sphere)->transform, \
// 		&world->hit.computations.over_point);
// 	temp = transform_point(&world->hit.computations.over_point, \
// 		&((t_sphere *)sphere)->transform, \
// 			&((t_sphere *)sphere)->appearance.texture.transform);
// 	((t_sphere *)sphere)->appearance.texture.map = spherical_map(&temp);
// 	texture_at(&((t_sphere *)sphere)->appearance.texture, \
// 		&((t_sphere *)sphere)->material, \
// 	&((t_sphere *)sphere)->appearance.texture.map);
// 	*colour = tuple_add(lighting(&lighting_info, \
// 		light, world->hit.computations.vectors, \
// 		world->hit.computations.over_point), *colour);
// }

// void	shade_cone(t_world *world, void *cone, t_tuple *colour, t_light *light)
// {
// 	t_info	lighting_info;
// 	t_tuple	temp;

// 	is_shadow(world, world->hit.computations.over_point, light);
// 	lighting_info = (t_info){
// 		.material = ((t_cone *)cone)->material
// 	};
// 	pattern_at(&((t_cone *)cone)->appearance.pattern, \
// 		&((t_cone *)cone)->material, ((t_cone *)cone)->transform, \
// 		&world->hit.computations.over_point);
// 	temp = transform_point(&world->hit.computations.over_point, \
// 		&((t_cone *)cone)->transform, \
// 			&((t_cone *)cone)->appearance.texture.transform);
// 	((t_cone *)cone)->appearance.texture.map = conical_map(&temp);
// 	texture_at(&((t_cone *)cone)->appearance.texture, \
// 		&((t_cone *)cone)->material, \
// 		&((t_cone *)cone)->appearance.texture.map);
// 	*colour = tuple_add(lighting(&lighting_info, \
// 		light, world->hit.computations.vectors, \
// 		world->hit.computations.over_point), *colour);
// }

// void	shade_cylinder(t_world *world, void *cylinder, t_tuple *colour,
// 	t_light *light)
// {
// 	t_info	lighting_info;
// 	t_tuple	temp;

// 	is_shadow(world, world->hit.computations.over_point, light);
// 	lighting_info = (t_info){
// 		.material = ((t_cylinder *)cylinder)->material
// 	};
// 	pattern_at(&((t_cylinder *)cylinder)->appearance.pattern, \
// 		&((t_cylinder *)cylinder)->material, \
// 			((t_cylinder *)cylinder)->transform, \
// 			&world->hit.computations.over_point);
// 	temp = transform_point(&world->hit.computations.over_point, \
// 		&((t_cylinder *)cylinder)->transform,
// 			&((t_cylinder *)cylinder)->appearance.texture.transform);
// 	((t_cylinder *)cylinder)->appearance.texture.map = cylindrical_map(&temp);
// 	texture_at(&((t_cylinder *)cylinder)->appearance.texture,
// 		&((t_cylinder *)cylinder)->material,
// 		&((t_cylinder *)cylinder)->appearance.texture.map);
// 	*colour = tuple_add(lighting(&lighting_info, \
// 		light, world->hit.computations.vectors, \
// 		world->hit.computations.over_point), *colour);
// }

// void	shade_cube(t_world *world, void *cube, t_tuple *colour,
// 	t_light *light)
// {
// 	t_info	lighting_info;
// 	t_tuple	temp;

// 	is_shadow(world, world->hit.computations.over_point, light);
// 	lighting_info = (t_info){
// 		.material = ((t_cube *)cube)->material
// 	};
// 	temp = transform_point(&world->hit.computations.over_point, \
// 		&((t_cube *)cube)->transform, \
// 			&((t_cube *)cube)->appearance.texture.transform);
// 	((t_cube *)cube)->appearance.texture.map = \
// 		cubic_map(&temp, &((t_cube *)cube)->appearance.texture);
// 	pattern_at(&((t_cube *)cube)->appearance.pattern, \
// 		&((t_cube *)cube)->material, ((t_cube *)cube)->transform, \
// 		&world->hit.computations.over_point);
// 	texture_at(&((t_cube *)cube)->appearance.texture,
// 		&((t_cube *)cube)->material,
// 		&((t_cube *)cube)->appearance.texture.map);
// 	*colour = tuple_add(lighting(&lighting_info, \
// 		light, world->hit.computations.vectors, \
// 		world->hit.computations.over_point), *colour);
// }













#include "RT.h"

void	shade_plane(t_world *world, void *plane, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;
	t_tuple	temp_point;
	t_tuple	temp_colour;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info.material = ((t_plane *)plane)->material;
	world->hit.computations.reflective = lighting_info.material.reflectiveness;
	temp_colour = lighting(&lighting_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	temp_point = transform_point(&world->hit.computations.over_point, \
		&((t_plane *)plane)->transform, \
		&((t_plane *)plane)->appearance.texture.transform);
	((t_plane *)plane)->appearance.texture.map = planar_map(&temp_point);
	if (((t_plane *)plane)->appearance.pattern.type > 0 || \
		((t_plane *)plane)->appearance.texture.type > 0)
		temp_colour = get_appearance_colour(&((t_plane *)plane)->appearance, \
			((t_plane *)plane)->transform, &world->hit.computations.over_point);
	*colour = tuple_add(*colour, temp_colour);
	*colour = tuple_add(*colour, reflected_colour(world, &world->hit.computations));
}

void	shade_sphere(t_world *world, void *sphere, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;
	t_tuple	temp_point;
	t_tuple	temp_colour;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info.material = ((t_sphere *)sphere)->material;
	world->hit.computations.reflective = lighting_info.material.reflectiveness;
	temp_colour = lighting(&lighting_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	temp_point = transform_point(&world->hit.computations.over_point, \
		&((t_sphere *)sphere)->transform, \
		&((t_sphere *)sphere)->appearance.texture.transform);
	((t_sphere *)sphere)->appearance.texture.map = spherical_map(&temp_point);
	if (((t_sphere *)sphere)->appearance.pattern.type > 0 || \
		((t_sphere *)sphere)->appearance.texture.type > 0)
		temp_colour = get_appearance_colour(&((t_sphere *)sphere)->appearance, \
			((t_sphere *)sphere)->transform, &world->hit.computations.over_point);
	*colour = tuple_add(*colour, temp_colour);
	*colour = tuple_add(*colour, reflected_colour(world, &world->hit.computations));
}

void	shade_cone(t_world *world, void *cone, t_tuple *colour, t_light *light)
{
	t_info	lighting_info;
	t_tuple	temp_point;
	t_tuple	temp_colour;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info.material = ((t_cone *)cone)->material;
	world->hit.computations.reflective = lighting_info.material.reflectiveness;
	temp_colour = lighting(&lighting_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	temp_point = transform_point(&world->hit.computations.over_point, \
		&((t_cone *)cone)->transform, \
		&((t_cone *)cone)->appearance.texture.transform);
	((t_cone *)cone)->appearance.texture.map = conical_map(&temp_point);
	if (((t_cone *)cone)->appearance.pattern.type > 0 || \
		((t_cone *)cone)->appearance.texture.type > 0)
		temp_colour = get_appearance_colour(&((t_cone *)cone)->appearance, \
			((t_cone *)cone)->transform, &world->hit.computations.over_point);
	*colour = tuple_add(*colour, temp_colour);
	*colour = tuple_add(*colour, reflected_colour(world, &world->hit.computations));
}

void	shade_cylinder(t_world *world, void *cylinder, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;
	t_tuple	temp_point;
	t_tuple	temp_colour;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info.material = ((t_cylinder *)cylinder)->material;
	world->hit.computations.reflective = lighting_info.material.reflectiveness;
	temp_colour = lighting(&lighting_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	temp_point = transform_point(&world->hit.computations.over_point, \
		&((t_cylinder *)cylinder)->transform, \
		&((t_cylinder *)cylinder)->appearance.texture.transform);
	((t_cylinder *)cylinder)->appearance.texture.map = cylindrical_map(&temp_point);
	if (((t_cylinder *)cylinder)->appearance.pattern.type > 0 || \
		((t_cylinder *)cylinder)->appearance.texture.type > 0)
		temp_colour = get_appearance_colour(&((t_cylinder *)cylinder)->appearance, \
			((t_cylinder *)cylinder)->transform, &world->hit.computations.over_point);
	*colour = tuple_add(*colour, temp_colour);
	*colour = tuple_add(*colour, reflected_colour(world, &world->hit.computations));
}

void	shade_cube(t_world *world, void *cube, t_tuple *colour,
	t_light *light)
{
	t_info	lighting_info;
	t_tuple	temp_point;
	t_tuple	temp_colour;

	is_shadow(world, world->hit.computations.over_point, light);
	lighting_info.material = ((t_cube *)cube)->material;
	world->hit.computations.reflective = lighting_info.material.reflectiveness;
	temp_colour = lighting(&lighting_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	temp_point = transform_point(&world->hit.computations.over_point, \
		&((t_cube *)cube)->transform, \
		&((t_cube *)cube)->appearance.texture.transform);
	((t_cube *)cube)->appearance.texture.map = \
		cubic_map(&temp_point,&((t_cube *)cube)->appearance.texture);
	if (((t_cube *)cube)->appearance.pattern.type > 0 || \
		((t_cube *)cube)->appearance.texture.type > 0)
		temp_colour = get_appearance_colour(&((t_cube *)cube)->appearance, \
			((t_cube *)cube)->transform, &world->hit.computations.over_point);
	*colour = tuple_add(*colour, temp_colour);
	*colour = tuple_add(*colour, reflected_colour(world, &world->hit.computations));
}
