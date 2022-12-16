











#include "RT.h"

t_ray	ray(t_tuple origin, t_tuple reflectv)
{
	t_tuple		direction;

	direction = normalize(tuple_sub(origin, reflectv));
	return ((t_ray){.origin = origin, .direction = direction});
}

t_tuple	reflected_colour(t_world *world, t_info *lighting_info)
{
	t_tuple	colour_refl;

	colour_refl = point(0, 0, 0);
	if (-EPSILON < lighting_info->material.reflectiveness \
		&& lighting_info->material.reflectiveness < EPSILON)
		return (colour_refl);
	world->ray = ray(world->hit.computations.over_point, \
		world->hit.computations.reflectv);
	colour_refl = colour_at(world);
	return (tuple_scale(colour_refl, lighting_info->material.reflectiveness));
}
