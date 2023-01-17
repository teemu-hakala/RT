











#include "RT.h"

t_tuple	colour_at(t_world *world, t_ray ray)
{
	t_tuple	colour;

	vec_clear(&world->intersections);
	intersect_world(world, ray);
	identify_hit(world, &world->hit);
	if (world->hit.hit_check == true)
	{
		prepare_computations(world, ray);
		colour = shade_hit(world);
		return (apply_filter(world, colour));
	}
	else
		return (vector(0, 0, 0));
}
