#include "RT.h"

// t_tuple	check_reflection_and_refraction(t_world *world, \
// 	t_info *light_info, t_tuple *colour)
// {
// 	t_tuple	reflected_col;
// 	t_tuple	refracted_col;
// 	t_fl	reflectance;

// 	reflected_col = reflected_colour(world, &world->hit.computations);
// 	refracted_col = refracted_colour(world, &world->hit.computations);
// 	if (light_info->material.reflectiveness > 0 && \
// 		light_info->material.transparency > 0)
// 	{
// 		reflectance = schlick(&world->hit.computations);
// 		if (reflectance > 1)
// 			printf("reflectance : %f\n", reflectance);
// 		return (*colour = tuple_add(*colour, \
// 			tuple_add(tuple_scale(reflected_col, reflectance), \
// 				tuple_scale(refracted_col, (1 - reflectance)))));
// 	}
// 	return (tuple_add(*colour, tuple_add(reflected_col, refracted_col)));
// }

// void	shade_object(t_world *world, t_tuple *colour,
// 	t_light *light, t_info *light_info)
// {
// 	t_tuple	surface_col;

// 	is_shadow(world, world->hit.computations.over_point, light);
// 	surface_col = lighting(light_info, light, \
// 		world->hit.computations.vectors, world->hit.computations.over_point);
// 	if (light_info->appearance.pattern.type > 0 || \
// 		light_info->appearance.texture.type > 0)
// 	{
// 		light_info->col = get_appearance_colour(light_info, \
// 			&world->hit.computations.over_point, light_info->f);
// 		surface_col = lighting(light_info, light, \
// 		world->hit.computations.vectors, world->hit.computations.over_point);
// 	}
// 	if (light_info->material.reflectiveness > 0 || \
// 		light_info->material.transparency > 0)
// 	{
// 		*colour = tuple_add(surface_col, \
// 			check_reflection_and_refraction(world, light_info, colour));
// 	}
// 	else
// 		*colour = tuple_add(*colour, surface_col);
// }