











#include "RT.h"

t_tuple	reflected_colour(t_world *world, t_info lighting_info)
{
	t_tuple	colour;

	colour = colour(0, 0, 0);
	if (-EPSILON < lighting_info-material &&
		lighting_info.material.reflectiveness < EPSILON)
		return (colour);
	reflect_ray = ray(world->hit.computations.over_point, \
		world->hit.computations.reflectv);
	colour = colour_at(world, reflect_ray);
	return (tuple_scale(colour, lighting_info.material.reflectiveness))
}
