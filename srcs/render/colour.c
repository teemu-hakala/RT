











#include "RT.h"

t_tuple	colour_at(t_world *world, t_ray ray)
{
	vec_clear(&world->intersections);
	intersect_world(world, ray);
	identify_hit(world, &world->hit);
	if (world->hit.hit_check == true)
	{
		prepare_object(world, world->hit.intersection.shape, \
		&world->hit.computations, ray);
		return (shade_hit(world));
	}
	else
		return (vector(0, 0, 0));
}
