
#include "RT.h"

void	shade_object(t_world *world, t_tuple *colour,
	t_light *light, t_info *light_info)
{
	t_tuple	surface_col;
	t_tuple	reflected_col;
	t_tuple	refracted_col;
	t_fl	reflectance;

	is_shadow(world, world->hit.computations.over_point, light);
	surface_col = lighting(light_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	if (light_info->appearance.pattern.type > 0 || \
		light_info->appearance.texture.type > 0)
	{
		light_info->col = get_appearance_colour(light_info, \
			&world->hit.computations.over_point, light_info->f);
		surface_col = lighting(light_info, light, \
		world->hit.computations.vectors, world->hit.computations.over_point);
	}
	reflected_col = reflected_colour(world, &world->hit.computations);
	refracted_col = refracted_colour(world, &world->hit.computations);
	if (light_info->material.reflectiveness > 0 && light_info->material.transparency > 0)
	{
		reflectance = schlick(&world->hit.computations);
		*colour = tuple_add(surface_col, \
			tuple_add(tuple_scale(reflected_col, reflectance), \
				tuple_scale(refracted_col, 1 - reflectance)));
	}
	else
		*colour = tuple_add(tuple_add(surface_col, reflected_col), refracted_col);
}

